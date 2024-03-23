#ifndef VECTORCAN_H
#define VECTORCAN_H

#include <QObject>
#include <QCanBus>
#include <QVector>
#include <QtDebug>
#include <QTimer>
#include <QMap>

class VectorCANBus : public QObject {
    Q_OBJECT

    QCanBusDevice* bus;

public:
    explicit VectorCANBus(QObject *parent = nullptr);
    ~VectorCANBus();

signals:
    void onVectorDataChanged();

public slots:
    void connect();

private:
    void setupFilters();

};

#endif // VECTORCAN_H
