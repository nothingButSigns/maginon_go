#include "connectionthread.h"

state connectionThread::connectionState()
{
    return conn_state;
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
