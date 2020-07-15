#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"

#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QList>


class Lightbulb: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant discoveredDevices READ getDevices NOTIFY devicesDiscovered)

public:
    Lightbulb();
    ~Lightbulb();

    QVariant getDevices();

    void searchForDevices();
    Q_INVOKABLE void connectToDevice(QString address);
    void discoverServiceDetails();

Q_SIGNALS:
    void devicesDiscovered();

private slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void discoveryCancelled();
    void discoveryError();

    // slots associated with connection attempt
    void deviceConnected();
    void deviceDisconnected();
    void addService();
    void serviceDiscoveryFinished();
    void connectionError();



private:
    QList <QObject *> foundDevices;
    QBluetoothDeviceInfo connectedDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = nullptr;
    QLowEnergyController *connectionController = nullptr;


};

#endif // LIGHTBULB_H
