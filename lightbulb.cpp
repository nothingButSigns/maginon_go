#include "lightbulb.h"
#include <QDebug>

Lightbulb::Lightbulb()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000); //set how much time the scan will take
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &Lightbulb::addDevice);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            [this]{emit discoveryFinished();});
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled,
            [this]{emit discoveryCanceled();});
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            [this]{emit discoveryError();});
}

Lightbulb::~Lightbulb()
{
    delete discoveryAgent;
    discoveryAgent = nullptr;
    qDeleteAll(foundDevices);

}

QVariant Lightbulb::getDevices()
{
    return QVariant::fromValue(foundDevices);
}

ConnectionThread *Lightbulb::connTh()
{
    return newConnection;
}

Device *Lightbulb::currDev()
{
    return currentConnection;
}

void Lightbulb::searchForDevices()
{
    emit searchingForDevices();
    foundDevices.clear();
    // Search only for Low Energy devices
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void Lightbulb::connectToDevice(QString devAddress)
{

    if(newConnection && (devAddress == newConnection->getAddress()))
    {
        currentConnection->getCurrentState();
        return;
    }


    for(auto dev : foundDevices)
    {
        Device *d = qobject_cast<Device *>(dev);
        if(d->bulbAddress() == devAddress)
        {
            currentConnection = d;
            break;
        }
    }

    newConnection = new ConnectionThread(devAddress);
    connect(newConnection, &ConnectionThread::stateConnected, this, &Lightbulb::stateConnected);
    //connect(newConnection, &ConnectionThread::stateConnectionError, this, &Lightbulb::stateConnected);
    newConnection->start();
}

void Lightbulb::addDevice(const QBluetoothDeviceInfo &device)
{
    Device *newDev = new Device(device);
    QString devName = device.name();

    // append only lightbulbs MAGINON
    if (devName == "B710")
        foundDevices.append(newDev);

}

void Lightbulb::stateConnected()
{
    qDebug() << "Connected";

    if(currentConnection)
        currentConnection->getCurrentState();
    else
        qDebug() << "currentConnection == null";

}
