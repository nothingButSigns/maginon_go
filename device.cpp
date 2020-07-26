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

void Device::getInitialState()
{
    readCharValue(this, STATE_HND);
}

void Device::retriveStateData(uint8_t *stateData)
{
    for (int i = 0; i<6; i++)
        qDebug() << "DATA: " << stateData[i];
}

QString Device::bulbName()
{
    return device.name();
}

QString Device::bulbAddress()
{
    QBluetoothAddress address = device.address();
    QString addr = address.toString();
    return addr;
}

int Device::actionState()
{
    return ActionState;
}

void Device::setActionState(int aState)
{
    switch (aState) {
        case state::WRITE_ERROR: {
            ActionState = WRITE_ERROR;
            break;
        }
        case state::READ_ERROR: {
            ActionState = READ_ERROR;
            break;
        }
        case state::WRITE_SUCCESS: {
            ActionState = WRITE_SUCCESS;
            break;
        }
        case state::READ_SUCCESS: {
            ActionState = READ_SUCCESS;
            break;
        }
    }

    emit actionStateChanged();
}
