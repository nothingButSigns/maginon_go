#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"
#include "maginon.h"
#include "actuators.h"
#include "connectionthread.h"

#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QList>
#include <glib.h>


class Lightbulb: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant discoveredDevices READ getDevices NOTIFY devicesDiscovered)
    Q_PROPERTY(ConnectionThread *connTh READ connTh NOTIFY connectionThreadChanged)
    Q_PROPERTY(Device *currDev READ currDev NOTIFY CurrentDeviceChanged)
    Q_PROPERTY(NOTIFY discoveryFinished)
    Q_PROPERTY(NOTIFY searchingForDevices)
    Q_PROPERTY(NOTIFY discoveryCancelled)
    Q_PROPERTY(NOTIFY discoveryError)

public:

    Lightbulb();
    ~Lightbulb();

    QVariant getDevices();
    ConnectionThread *connTh();
    Device *currDev();
    int connectionState();

    Q_INVOKABLE void searchForDevices();
    Q_INVOKABLE void connectToDevice(QString devAddress);


Q_SIGNALS:
    void devicesDiscovered();
    void connectionThreadChanged();
    void CurrentDeviceChanged();
    void connectionStateChanged();

    void searchingForDevices();
    void discoveryFinished();
    void discoveryCanceled();
    void discoveryError();


private slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void stateConnected();

private:
    ConnectionThread *newConnection = nullptr;
    QList <QObject *> foundDevices;
    Device *currentConnection = nullptr;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = nullptr;
};

#endif // LIGHTBULB_H
