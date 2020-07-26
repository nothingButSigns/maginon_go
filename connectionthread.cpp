#include "connectionthread.h"
#include <string>

ConnectionThread::ConnectionThread()
{

}

ConnectionThread::ConnectionThread(QString devAddress)
{
    QByteArray toLatin = devAddress.toUtf8();
    std::string var = toLatin.toStdString();
    devStr = std::string(var);

    dstAddress = devStr.c_str();
}

int ConnectionThread::intConnectionState()
{
    return conn_state;
}

void ConnectionThread::setConnectionState(int currentState)
{

    switch (currentState) {
    case state::STATE_CONNECTED: {
        conn_state = connState::CONNECTED;
        emit stateConnected(dstAddress);
        break;
    }
    case state::STATE_CONNECTING: {
        conn_state = connState::CONNECTING;
        emit stateDisconnected();
        break;
    }
    case state::STATE_DISCONNECTED: {
        conn_state = connState::DISCONNECTED;
        emit stateDisconnected();
        break;
    }
    default:
        break;
    }
    emit connectionStateChanged();
}
