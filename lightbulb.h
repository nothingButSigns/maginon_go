#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"
#include "maginon.h"

#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QList>

#include <glib.h>
#include "actuators.h"
#include "connectionthread.h"
#include "device.h"

class Lightbulb: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant discoveredDevices READ getDevices NOTIFY devicesDiscovered)
    Q_PROPERTY(bool onOff READ getOnOff NOTIFY onOffChanged)
    Q_PROPERTY(ConnectionThread *connTh READ connTh NOTIFY connectionThreadChanged)
    Q_PROPERTY(Device *currDev READ currDev NOTIFY CurrentDeviceChanged)
    //Q_PROPERTY(int connectionState READ connectionState NOTIFY connectionStateChanged)

public:

    Lightbulb();
    ~Lightbulb();

    QVariant getDevices();
    //state connectionState();
    ConnectionThread *connTh();
    Device *currDev();
    int connectionState();

    void searchForDevices();

    Q_INVOKABLE void executeCommand(int param);
    Q_INVOKABLE void connectToDevice(QString devAddress);


    // functions associated with device state and control
    void getInitialState();

    // functions associated with device state and control Q_PROPERTY
    bool getOnOff();



Q_SIGNALS:
    void devicesDiscovered();
    void connectionThreadChanged();
    void CurrentDeviceChanged();
    void connectionStateChanged();

    // signals associated with device state and control
    void onOffChanged();

private slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void discoveryCancelled();
    void discoveryError();

    void signalfromdevice();

    // slots associated with connection attempt
    void connectionError();
    void stateConnected();


private:
    ConnectionThread *newConnection = nullptr;
    QList <QObject *> foundDevices;
    Device *currentConnection = nullptr;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = nullptr;

};

#endif // LIGHTBULB_H
