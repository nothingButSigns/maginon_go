#include "connectionthread.h"
#include <string>

ConnectionThread::ConnectionThread(QString devAddress)
{
    QByteArray toLatin = devAddress.toUtf8();
    std::string var = toLatin.toStdString();
    devStr = std::string(var);

    dstAddress = devStr.c_str();
}

int ConnectionThread::connectionState()
{
    return conn_state;
}

void ConnectionThread::setConnectionState(state currentState)
{

    switch (currentState) {
    case state::STATE_CONNECTED: {
        conn_state = _ConnectionState::CONNECTED;
        emit stateConnected();
        break;
    }
    case state::STATE_CONNECTING: {
        conn_state = _ConnectionState::CONNECTING;
        emit stateDisconnected();
        break;
    }
    case state::STATE_DISCONNECTED: {
        conn_state = _ConnectionState::DISCONNECTED;
        emit stateDisconnected();
        break;
    }
    case state::STATE_CONNECTION_ERROR: {
        conn_state = _ConnectionState::CONNECTION_ERROR;
        emit stateConnectionError();
        break;
    }
    default:
        break;
    }
    emit connectionStateChanged();
}

QString ConnectionThread::getAddress()
{
    return QString::fromStdString(devStr);
}

void ConnectionThread::disconnect()
{
    initiateDisconnection();
    delete dstAddress;
    exit();
    emit stateDisconnected();
}
