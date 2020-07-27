#ifndef CONNECTTIONHREAD_H
#define CONNECTTIONHREAD_H
#include <QThread>
#include <QObject>
#include "actuators.h"



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
        CONNECTED
    };
    Q_ENUM(_ConnectionState)

    ConnectionThread();
    ConnectionThread(QString devAddress);;

   // state connectionState();
    int connectionState();
    void setConnectionState(state currentState);

Q_SIGNALS:
    void stateConnected();
    void stateConnecting();
    void stateDisconnected();
    void connectionStateChanged();

private:
    _ConnectionState conn_state;
    std::string devStr = "";
    const char* dstAddress = nullptr;
};

#endif // CONNECTTHREAD_H
