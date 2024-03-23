#include "canbus/vectorcanbus.hpp"

void VectorCANBus::connect(QString canInterface) {

    if (!QCanBus::instance()->plugins().contains(QStringLiteral("vectorcan"))) {
        qDebug() << "[VectorCANBus] 'vectorcan' plugin not available!";
        return;
    } else {
        qDebug() << "[VectorCANBus] 'vectorcan' plugin available";
    }

    QString errorString;
    bool connectionStatus;

    bus = QCanBus::instance()->createDevice(
        QStringLiteral("vectorcan"), canInterface, &errorString);
    if (!bus) {
        qDebug() << "[VectorCANBus] error creating CAN device: " << errorString;
        return;
    } else {
        qDebug() << "[VectorCANBus] connecting CAN interface: " << canInferface;
        bus->connectDevice();
        // TODO: connect device
    }

//    if (!connectionStatus) {
//        qDebug() << "Connection Failed!";
//        return;
//    }

//    m_setupDone = true;
//    qDebug() << "can1 connect successful";
}


