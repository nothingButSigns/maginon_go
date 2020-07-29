#ifndef CONNECTTIONHREAD_H
#define CONNECTTIONHREAD_H

#include "actuators.h"

#include <QThread>
#include <QObject>


class ConnectionThread: public QThread
{
    Q_OBJECT
    Q_PROPERTY(int connectionState READ connectionState NOTIFY connectionStateChanged)

    void run() override {
        connectToBulb(this, dstAddress);
    }

public:


    enum _ConnectionState {
        DISCONNECTED,
        CONNECTING,
        CONNECTED,
        CONNECTION_ERROR
    };
    Q_ENUM(_ConnectionState)

    ConnectionThread() = default;
    ConnectionThread(QString devAddress);

    int connectionState();
    void setConnectionState(state currentState);
    QString getAddress();

    void disconnect();

Q_SIGNALS:
    void stateConnected();
    void stateConnecting();
    void stateDisconnected();
    void stateConnectionError();
    void connectionStateChanged();

private:
    _ConnectionState conn_state;
    std::string devStr = "";
    const char* dstAddress = nullptr;
};

#endif // CONNECTTHREAD_H
