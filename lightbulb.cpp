#include "lightbulb.h"

Lightbulb::Lightbulb()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000); //set how much time the scan will take
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &Lightbulb::addDevice);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
            &Lightbulb::discoveryFinished);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this,
            &Lightbulb::discoveryCancelled);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &Lightbulb::discoveryError);


}

Lightbulb::~Lightbulb()
{
    delete discoveryAgent;
    discoveryAgent = nullptr;
    delete connectionController;
    connectionController = nullptr;
    qDeleteAll(foundDevices);

}

QVariant Lightbulb::getDevices()
{
    return QVariant::fromValue(foundDevices);
}

void Lightbulb::searchForDevices()
{
    foundDevices.clear();
    // Search only for Low Energy devices
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

}

void Lightbulb::connectToDevice(QString address)
{
    Device *lb = nullptr;

    for (auto i : foundDevices)
    {
        lb = qobject_cast<Device *>(i);
        if(lb->getDevice().address().toString() == address)
            break;
    }

    if(connectionController)
    {
        connectionController->disconnectFromDevice();
        delete connectionController;
        connectionController = nullptr;
    }

    connectedDevice = lb->getDevice();

    connectionController = QLowEnergyController::createCentral(connectedDevice);
    connect(connectionController, &QLowEnergyController::connected, this, &Lightbulb::deviceConnected);
    connect(connectionController, &QLowEnergyController::disconnected, this, &Lightbulb::deviceDisconnected);
    connect(connectionController, &QLowEnergyController::serviceDiscovered, this, &Lightbulb::addService);
    connect(connectionController, &QLowEnergyController::discoveryFinished, this, &Lightbulb::serviceDiscoveryFinished);
    connect(connectionController, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),
            this, &Lightbulb::connectionError);

    connectionController->setRemoteAddressType(QLowEnergyController::RandomAddress);

    connectionController->connectToDevice();

}

void Lightbulb::addDevice(const QBluetoothDeviceInfo &device)
{
    Device *newDev = new Device(device);
    QString devName = device.name();

    // append only lightbulbs MAGINON
    if (devName == "B710")
        foundDevices.append(newDev);

}

void Lightbulb::discoveryFinished()
{


}

void Lightbulb::discoveryCancelled()
{

}

void Lightbulb::discoveryError()
{
    qDebug() << "DiscoveryError";

}

void Lightbulb::deviceConnected()
{
    qDebug() << "Device connected";

}

void Lightbulb::deviceDisconnected()
{

}

void Lightbulb::addService()
{

}

void Lightbulb::serviceDiscoveryFinished()
{
    qDebug() << "Service discovery finished";

}

void Lightbulb::connectionError()
{
    qDebug() << "Connection error";

}
