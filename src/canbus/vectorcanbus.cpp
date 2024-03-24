#include <QVariant>
#include <QMetaObject>
#include "vectorcanbus.hpp"

VectorCANBus::VectorCANBus(QString _channel, QObject *parent) :
    channel(_channel), QObject(parent) {
    QMetaObject::invokeMethod(this, &VectorCANBus::connectToCAN, Qt::QueuedConnection);
}

VectorCANBus::~VectorCANBus() {
    qDebug() << "[VectorCANBus] disconnecting and deleting bus";
    if (device->state() == QCanBusDevice::ConnectedState)
        device->disconnectDevice();
}

void VectorCANBus::connectToCAN() {
    // check that QCanBus provides the VectorCAN plugin
    if (!QCanBus::instance()->plugins().contains(QStringLiteral("vectorcan")))
        qFatal() << "[VectorCANBus] 'vectorcan' plugin unavailable";
    qDebug() << "[VectorCANBus] 'vectorcan' plugin available";

    // initialize bus device
    QString errorString;
    device = QCanBus::instance()->createDevice(
        QStringLiteral("vectorcan"), channel, &errorString);
    if (!device)
        qFatal() << "[VectorCANBus] error creating CAN device: " << errorString;

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
    if (!connectionStatus)
        qFatal() << "[VectorCANBus] connection failed";
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
