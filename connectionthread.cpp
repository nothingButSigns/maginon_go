#include "connectionthread.h"

state connectionThread::connectionState()
{
    return conn_state;
}

QString connectionThread::randomString()
{
    return rStr;
}

void connectionThread::setConnectionState(state currentState)
{
    conn_state = currentState;

    switch (currentState) {
        case STATE_CONNECTED: {
            emit stateConnected();
            break;
        }
        case STATE_CONNECTING: {
            emit stateDisconnected();
            break;
        }
        case STATE_DISCONNECTED: {
            emit stateDisconnected();
            break;
        }
        default:
            break;
    }
}

void connectionThread::setRandomString(QString newString)
{
    rStr = newString;
    emit randomStringChanged();
}
