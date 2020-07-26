#ifndef CONNECTTIONHREAD_H
#define CONNECTTIONHREAD_H
#include <QThread>
#include <QObject>
#include "actuators.h"



class ConnectionThread: public QThread
{
    Q_OBJECT

    Q_PROPERTY(int connectionState READ intConnectionState WRITE setConnectionState NOTIFY connectionStateChanged)

    void run() override {
        connectToBulb(this, dstAddress);
    }
//"80:30:DC:05:A9:96"
public:


    enum connState {
        DISCONNECTED,
        CONNECTING,
        CONNECTED
    };
    Q_ENUM(connState)

    ConnectionThread();
    ConnectionThread(QString devAddress);;

   // state connectionState();
    int intConnectionState();
    void setConnectionState(int currentState);

Q_SIGNALS:
    void stateConnected(QString(dstAddress));
    void stateConnecting();
    void stateDisconnected();
    void connectionStateChanged();


private:
    connState conn_state;
    std::string devStr = "";
    const char* dstAddress = nullptr;
};

#endif // CONNECTTHREAD_H
