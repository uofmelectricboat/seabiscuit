#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>

class canbus : public QObject
{
    Q_OBJECT
public:
    explicit canbus(QObject *parent = nullptr);

signals:

};

#endif // CANBUS_H
