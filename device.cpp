#include "device.h"


void Device::turnOnOff()
{
    if(BulbState)
        writeCharValue(_OFF, WRITE_HND);
    else
        writeCharValue(_ON, WRITE_HND);

    getInitialState();
}

Device::Device(const QBluetoothDeviceInfo &d)
{
    device = d;
}

Device::Device(const Device &d)
{
    this->d = nullptr;
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
    // get ON/OFF state info
    if(stateData[0] < static_cast<int>(OFF) || stateData[0] > static_cast<int>(ON))
        qDebug() << "Cannot determine whether the bulb is on or off";
    else
    {
        BulbState = static_cast<_BulbState>(stateData[0]);
        emit bulbStateChanged();
    }


    // get color info
    lightColor[0] = stateData[2];
    lightColor[1] = stateData[3];
    lightColor[2] = stateData[4];

        // check whether data is valid
        if(stateData[1] > static_cast<int>(RLUM_MIN) && stateData[1] < static_cast<int>(MAX_LUM))
        {
            quint8 rcvData = stateData[1];
            bool isValuePresent = true;

            //check whether received luminosity value has corresponding enum value for white light
            [&isValuePresent, rcvData] {
                switch(rcvData) {
                    case static_cast<int>(MIN_LUM): break;
                    case static_cast<int>(LUM1): break;
                    case static_cast<int>(LUM2): break;
                    case static_cast<int>(LUM3): break;
                    case static_cast<int>(MAX_LUM): break;
                default: isValuePresent = false;
                }
            }();

            if(isValuePresent)
            {
                luminosity = static_cast<Luminosity>(rcvData);
                luminosityRGB = R_UNKNOWN;
                qDebug() << "Luminosity value for white light has been found";
            }
            else
            {
                isValuePresent = true;

                //check whether received luminosity value has corresponding enum value
                [&isValuePresent, rcvData] {
                    switch(rcvData) {
                        case static_cast<int>(RLUM_MIN): break;
                        case static_cast<int>(RLUM1): break;
                        case static_cast<int>(RLUM2): break;
                        case static_cast<int>(RLUM3): break;
                        case static_cast<int>(RLUM4): break;
                        case static_cast<int>(RLUM5): break;
                        case static_cast<int>(RLUM6): break;
                        case static_cast<int>(RLUM7): break;
                        case static_cast<int>(RLUM_MAX): break;
                    default: isValuePresent = false;
                    }
                }();

                if(isValuePresent)
                {
                    luminosityRGB = static_cast<LuminosityRGB>(rcvData);
                    luminosity = UNKNOWN;
                    qDebug() << "Luminosity value for RGB light has been found";
                }
                else
                    qDebug() << "Luminosity level cannot be retrieved";
            }

        }
        else
            qDebug() << "Luminosity data is invalid. Luminosity level cannot be retrieved";


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

bool Device::bulbState()
{
    return BulbState;
}

void Device::setActionState(int aState)
{
    qDebug() << "\nsetting aaction state";
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
