#include <QVariant>
#include "vectorcanbus.hpp"

VectorCANBus::~VectorCANBus() {
    qDebug() << "[VectorCANBus] disconnecting and deleting bus";
    if (device->state() == QCanBusDevice::ConnectedState)
        device->disconnectDevice();
}

void VectorCANBus::connectToCAN(QString channel) {
    // check that QCanBus provides the VectorCAN plugin
    if (!QCanBus::instance()->plugins().contains(QStringLiteral("vectorcan"))) {
        qDebug() << "[VectorCANBus] 'vectorcan' plugin unavailable";
        return;
    }
    qDebug() << "[VectorCANBus] 'vectorcan' plugin available";

    // initialize device
    QString errorString;
    device = QCanBus::instance()->createDevice(
        QStringLiteral("vectorcan"), channel, &errorString);
    if (!device) {
        qDebug() << "[VectorCANBus] error creating CAN device: " << errorString;
        return;
    }

    // establish connections
    bool connectionStatus = false;
    qDebug() << "[VectorCANBus] connecting CAN interface: " << channel;
    connect(device, &QCanBusDevice::errorOccurred,
            this, &VectorCANBus::processErrors);
    connect(device, &QCanBusDevice::stateChanged,
            this, &VectorCANBus::processStateChange);
    connect(device, &QCanBusDevice::framesReceived,
            this, &VectorCANBus::processReceivedFrames);
    connectionStatus = device->connectDevice();
    if (!connectionStatus) {
        qDebug() << "[VectorCANBus] connection failed";
        return;
    }
    qDebug() << "[VectorCANBus] connection succeeded";
}

void VectorCANBus::processStateChange() {
    qDebug() << "[VectorCANBus] QCanBusDevice::stateChanged: " << device->state();
}

void VectorCANBus::processErrors() {
    qDebug() << "[VectorCANBus] QCanBusDevice::errorOccurred: " << device->errorString();
}

void VectorCANBus::processReceivedFrames() {
    qDebug() << "[VectorCANBus] processing " << device->framesAvailable() << " frames";
    QList<QCanBusFrame> frames = device->readAllFrames();
    for (auto frame : frames) {
        if (callbacks.find(frame.frameId()) == callbacks.end())
            continue;
        for (auto callback : callbacks[frame.frameId()])
            callback(frame.payload());
    }
}

void VectorCANBus::registerFrameHandler(int id, std::function<void(QByteArray)> callback) {
    callbacks[id].push_back(callback);
    QCanBusDevice::Filter filter;
    filter.frameId = id;
    filter.frameIdMask = 0xFFF;
    filter.format=QCanBusDevice::Filter::MatchBaseAndExtendedFormat;
    filter.type = QCanBusFrame::InvalidFrame;
    filterList.append(filter);
    device->setConfigurationParameter(
        QCanBusDevice::RawFilterKey, QVariant::fromValue(filterList));
}
