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

void Lightbulb::executeCommand(int param)
{
    const char* addr = "80:30:DC:05:A9:96";
    qDebug() << "inside executeCOmmand; PARAM = " << param;

    if(param == 1)
        writeCharValue(LUM2, HAND_LAMP);
    else if (param == 2)
        writeCharValue(MIN_LUM1, HAND_LAMP);



}

void Lightbulb::exploreCharacteristics(quint8 serviceIndex)
{
    /* const_cast is necessary here cause 'Services' QList constains pointers to const objects
     * the const is removed here to call 'discoverDetails()' function which has no 'const' specifier,
     * so cannot be called for 'const' objects
     */
    QLowEnergyService *service = const_cast<QLowEnergyService*>(Services.at(serviceIndex));


    if(service->state() == QLowEnergyService::DiscoveryRequired)
    {
        connect(service, &QLowEnergyService::stateChanged, this, &Lightbulb::discoverServiceDetails);
        service->discoverDetails();
        return;
    }

    QList<QLowEnergyCharacteristic> characteristics = service->characteristics();

    for(auto ch :  characteristics)
    {
         QLowEnergyCharacteristic *charPtr = &ch;
         qDebug() << charPtr->uuid().toString();
        Characteristics.append(charPtr);

        if(charPtr->uuid().toString() == CONTROL_CHARACTERISTICS)
            cCharacteristic = charPtr;
        else if(charPtr->uuid().toString() == NOTIFY_CHARACTERISTICS)
            nCharacteristic = charPtr;

    }
}

void Lightbulb::discoverServiceDetails(QLowEnergyService::ServiceState servState)
{
    if(servState != QLowEnergyService::ServiceDiscovered)
        return;

    QLowEnergyService *service = qobject_cast <QLowEnergyService *> (sender());

    if(!service)
        return;

    QList <QLowEnergyCharacteristic> characteristics = service->characteristics();


    for(auto ch :  characteristics)
    {
        QLowEnergyCharacteristic *charPtr = &ch;
        qDebug() << charPtr->uuid().toString();
        Characteristics.append(charPtr);
qDebug() << "discovering service details";
        if(charPtr->uuid().toString() == CONTROL_CHARACTERISTICS)
            cCharacteristic = charPtr;
        else if(charPtr->uuid().toString() == NOTIFY_CHARACTERISTICS)
            nCharacteristic = charPtr;

        }
}

void Lightbulb::lightbulbDetails(QLowEnergyService::ServiceState servState)
{
    if(servState != QLowEnergyService::ServiceDiscovered)
    {
        qDebug() << "no ServiceDIscovered";
        return;
    }

    qDebug() << "ServiceDIscovered";

    QLowEnergyService *service = qobject_cast <QLowEnergyService *> (sender());

    if(!service)
        return;

//    QList<QLowEnergyCharacteristic> chars = service->characteristics();

//    for(auto i : chars)
//        qDebug() << "char uuid: " << i.uuid().toString();

    const QString linkCHar = CONTROL_CHARACTERISTICS;
    const QBluetoothUuid buuid = QBluetoothUuid(linkCHar);

    const QLowEnergyCharacteristic link = service->characteristic(buuid);

    if(link.isValid())
    {
        qDebug() << "link iss valid";
        qDebug() << link.name();
        qDebug() << link.uuid().toString();
        qDebug() << link.handle();
    }

    else
        qDebug() << "link is invalid";

}

void Lightbulb::createObject(const QBluetoothUuid &uuid)
{
    QLowEnergyService *service = connectionController->createServiceObject(uuid);

    if(service->state() == QLowEnergyService::DiscoveryRequired)
    {
        connect(service, &QLowEnergyService::stateChanged, this, &Lightbulb::lightbulbDetails);

        service->discoverDetails();
        return;
    }

}

bool Lightbulb::getOnOff()
{

}

void Lightbulb::connectToThread()
{
    connectThread *newThread = new connectThread();
    newThread->start();

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

    if(Services.empty())
        connectionController->discoverServices();
    else
    {
        qDebug() << "services discovered";
       // qDebug() << cCharacteristic->uuid().toString();
       // qDebug() << nCharacteristic->uuid().toString();

    }



}

void Lightbulb::deviceDisconnected()
{
    qDebug() << "dev disconnected. Reconnecting..";
    connectionController->connectToDevice();
}

void Lightbulb::addService(const QBluetoothUuid &uuid)
{
    const QString linkServ = CONTROL_SERVICE;
    const QBluetoothUuid suuid = QBluetoothUuid(linkServ);
    QLowEnergyService *service = connectionController->createServiceObject(suuid);
    qDebug() << "Service uuid: " << suuid.toString();
    Services.append(service);





//    if(service->serviceUuid().toString() == CONTROL_SERVICE)
//        lightbulbService = service;

}

void Lightbulb::serviceDiscoveryFinished()
{
    qDebug() << "Service discovery finished";
     QLowEnergyService * ser = const_cast<QLowEnergyService *>(Services.at(2));



    if(ser->state() == QLowEnergyService::DiscoveryRequired)
    {
        connect(ser, &QLowEnergyService::stateChanged, this, &Lightbulb::lightbulbDetails);

        ser->discoverDetails();
        return;
    }

    QLowEnergyCharacteristicData charData;
    const QString linkCHar = CONTROL_CHARACTERISTICS;
    const QBluetoothUuid buuid = QBluetoothUuid(linkCHar);

   QLowEnergyService * service = const_cast<QLowEnergyService *>(Services.at(3));


    const QLowEnergyCharacteristic link = service->characteristic(buuid);



//    connect(lightbulbService, &QLowEnergyService::characteristicWritten, this, &Lightbulb::onOffCHarWritten);
//    lightbulbService->QLowEnergyService::writeCharacteristic(link, QByteArray::fromHex("aa0afc3a86010a010001280d"));

}

void Lightbulb::connectionError()
{
    qDebug() << "Connection error";

}

void Lightbulb::onOffCHarWritten(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    qDebug() << "Value written";

}
