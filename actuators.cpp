#include "actuators.h"
#include "connectionthread.h"
#include "device.h"

void setConnectionState(void *callerPtr, state currentState)
{
    if(currentState == READ_ERROR || currentState == WRITE_ERROR
            || currentState == READ_SUCCESS || currentState == WRITE_SUCCESS)
    {
        qDebug() << "\n Setting device state..";
        Device *dev = static_cast<Device *>(callerPtr);
        dev->setActionState(currentState);
    }
    else
    {
        ConnectionThread *cTh = static_cast<ConnectionThread *>(callerPtr);
        cTh->setConnectionState(currentState);
    }

}

void sendStateData(void *rcvPtr, void *data)
{
    Device *dev = static_cast<Device *>(rcvPtr);
    uint8_t* stateData = static_cast<uint8_t*>(data);
    dev->retriveStateData(stateData);

}

