#ifndef DEVICE_H
#define DEVICE_H

#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QAbstractListModel>
#include <QObject>

class Device: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bulbName READ bulbName WRITE setBulbName NOTIFY bulbNameChanged)
    Q_PROPERTY(QString bulbAddress READ bulbAddress WRITE setBulbAddress NOTIFY bulbAddressChanged)

public:
    Device() = default;
    Device(const QBluetoothDeviceInfo &d);
    ~Device();
    QBluetoothDeviceInfo getDevice();

    QString bulbName();
    QString bulbAddress();
    void setBulbName(QString name);
    void setBulbAddress(QString address);

Q_SIGNALS:
    void bulbNameChanged();
    void bulbAddressChanged();


private:
    QBluetoothDeviceInfo device;
    QString name;
    QString address;

};

#endif // DEVICE_H
