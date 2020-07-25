#include "actuators.h"
#include "connectionthread.h"

void execute(const char* address, const char* value, int handler);

void setConnectionState(void *callerPtr, state currentState)
{
    connectionThread *cTh = static_cast<connectionThread *>(callerPtr);
    cTh->setConnectionState(currentState);
    cTh->setRandomString("CONNECTED");
}
