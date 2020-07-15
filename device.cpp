#include "device.h"


Device::Device(const QBluetoothDeviceInfo &d)
{
    device = d;
}

Device::~Device()
{

}

QBluetoothDeviceInfo Device::getDevice()
{
    return device;
}

QString Device::bulbName()
{
    return device.name();
}

QString Device::bulbAddress()
{
    return device.address().toString();
}

void Device::setBulbName(QString name)
{
    this->name = name;
}

void Device::setBulbAddress(QString address)
{
    this->address = address;
}
