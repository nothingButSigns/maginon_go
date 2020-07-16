#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"
#include "maginon.h"

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
    Q_PROPERTY(bool onOff READ getOnOff NOTIFY onOffChanged)

public:
    Lightbulb();
    ~Lightbulb();

    QVariant getDevices();

    void searchForDevices();
    Q_INVOKABLE void connectToDevice(QString address);
    void exploreCharacteristics(quint8 serviceIndex);
    void discoverServiceDetails();

    // functions associated with device state and control
    void getInitialState();

    // functions associated with device state and control Q_PROPERTY
    bool getOnOff();

Q_SIGNALS:
    void devicesDiscovered();

    // signals associated with device state and control
    void onOffChanged();

private slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void discoveryCancelled();
    void discoveryError();

    // slots associated with connection attempt
    void deviceConnected();
    void deviceDisconnected();
    void addService(const QBluetoothUuid &uuid);
    void serviceDiscoveryFinished();
    void connectionError();



private:
    QList <QObject *> foundDevices;
    QBluetoothDeviceInfo connectedDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = nullptr;
    QLowEnergyController *connectionController = nullptr;

    QList <const QLowEnergyService *> Services;
    const QLowEnergyService *lightbulbService = nullptr;


};

#endif // LIGHTBULB_H
