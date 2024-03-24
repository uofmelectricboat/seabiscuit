// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "canbus/vectorcanbus.hpp"
#include "systemmetrics.h"

QObject *dashboard;

void callback(QByteArray canPayload);

int main(int argc, char *argv[]) {
    set_qt_environment();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    dashboard = engine.rootObjects().first();

    VectorCANBus device("can2");
    device.registerFrameHandler(535888869, callback);
    device.registerFrameHandler(535888870, callback);

    return app.exec();
}

void callback(QByteArray canPayload) {
    if (dashboard == nullptr)
        return;

    // split CAN data into separate bytes
    unsigned char frameNumber = canPayload[0];
    unsigned char payload[CANMessageFrames][CANMessageBytes];
    for (int i = 0; i < CANMessageBytes; i++)
        payload[frameNumber][i] = canPayload[i];

    // set properties
    switch (frameNumber) {
    case 0:
        dashboard->setProperty("app_VCU_SPEED_MPH", getValue(payload, VCU_SPEED_MPH));
        dashboard->setProperty("app_VCU_BATTERY_CHARGE_PERCENTAGE", getValue(payload, VCU_BATTERY_CHARGE_PERCENTAGE));
        dashboard->setProperty("app_VCU_BATTERY_TEMPERATURE_DEGREES_C", getValue(payload, VCU_BATTERY_TEMPERATURE_DEGREES_C));
        dashboard->setProperty("app_VCU_MOTOR_TEMPERATURE_DEGREES_C", getValue(payload, VCU_MOTOR_TEMPERATURE_DEGREES_C));
        dashboard->setProperty("app_VCU_BATTERY_POWER_KW", getValue(payload, VCU_BATTERY_POWER_KW));
        dashboard->setProperty("app_VCU_WATER_STATUS", getValue(payload, VCU_WATER_STATUS));
        dashboard->setProperty("app_VCU_COOLING_SYSTEM_STATUS", getValue(payload, VCU_COOLING_SYSTEM_STATUS));
    case 1:
        dashboard->setProperty("app_VCU_ENGINE_SPEED_RPM", getValue(payload, VCU_ENGINE_SPEED_RPM));
    }
}
