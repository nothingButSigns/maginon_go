#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"
#include "maginon.h"

#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QLowEnergyCharacteristicData>
#include <QLowEnergyDescriptorData>
#include <QLowEnergyServiceData>
#include <QList>

#include <glib.h>
#include "actuators.h"
#include "connectionthread.h"


class Lightbulb: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant discoveredDevices READ getDevices NOTIFY devicesDiscovered)
    Q_PROPERTY(bool onOff READ getOnOff NOTIFY onOffChanged)

public:
    Lightbulb();
    ~Lightbulb();

    QVariant getDevices();
    //state connectionState();

    void searchForDevices();
   // Q_INVOKABLE void connectToDevice(QString address);
    Q_INVOKABLE void executeCommand(int param);
    Q_INVOKABLE void connectToThread();
    void exploreCharacteristics(quint8 serviceIndex);

    void discoverServiceDetails(QLowEnergyService::ServiceState servState);

    ////Experimental
    void lightbulbDetails(QLowEnergyService::ServiceState servState);

    void createObject(const QBluetoothUuid &uuid);
    ////

    // functions associated with device state and control
    void getInitialState();

    // functions associated with device state and control Q_PROPERTY
    bool getOnOff();

    ////Experimental slots
public slots:
    void onOffCHarWritten(const QLowEnergyCharacteristic &info,
                          const QByteArray &value);



Q_SIGNALS:
    void devicesDiscovered();
    void connectionStateChanged();

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
    void notifyState();

    //friend void setConnectionState(state connState);


private:
    connectionThread *newConnection = nullptr;
    QList <QObject *> foundDevices;
    QBluetoothDeviceInfo connectedDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = nullptr;
    QLowEnergyController *connectionController = nullptr;

    QList <const QLowEnergyService *> Services;
    QList <const QLowEnergyCharacteristic *> Characteristics;

    const QLowEnergyService *lightbulbService = nullptr;

    QLowEnergyCharacteristic *cCharacteristic = nullptr;
    QLowEnergyCharacteristic *nCharacteristic = nullptr;


};

#endif // LIGHTBULB_H
