#ifndef VECTORCAN_H
#define VECTORCAN_H

#include <QObject>
#include <QCanBus>
#include <QtDebug>
#include <QCanBusDevice>
#include <QByteArray>
#include <QString>
#include <QVector>
#include <unordered_map>
#include <vector>

class VectorCANBus : public QObject {
    Q_OBJECT

public:
    explicit VectorCANBus(QString _channel, QObject *parent = nullptr);
    ~VectorCANBus();

private:
    QCanBusDevice* device;
    std::unordered_map<int, std::vector<std::function<void(QByteArray)>>> callbacks;
    QVector<QCanBusDevice::Filter> filterList;
    QString channel;

    void processReceivedFrames();
    void processErrors();
    void processStateChange();

public slots:
    /*
     * The VectorCAN plugin provides 64 channels (defined by XL_CONFIG_MAX_CHANNELS in
     * the Vector API) from can0 to can63. Some of these channels can be virtual, and
     * therefore can be used without actual CAN hardware. To find out the virtual
     * channels, the program "Vector Hardware Config" (vcanconf.exe) can be used
     * which is included in Vector's driver package. The availableDevices() method
     * returns a list of currently available devices.
     */
    void connectToCAN();

    void registerFrameHandler(int id, std::function<void(QByteArray)> callback);

};

#endif // VECTORCAN_H
