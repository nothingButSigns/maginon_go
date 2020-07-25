#ifndef CONNECTTIONHREAD_H
#define CONNECTTIONHREAD_H
#include <QThread>
#include <QObject>
#include "actuators.h"


class connectionThread: public QThread
{
    Q_OBJECT
    Q_ENUM(state)
    Q_PROPERTY(state connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)

    void run() override {
        connectToBulb(this);
    }

public:
    connectionThread(){};

    state connectionState();
    void setConnectionState(state currentState);

Q_SIGNALS:
    void stateConnected();
    void stateConnecting();
    void stateDisconnected();
    void connectionStateChanged();


private:
    state conn_state;
};

#endif // CONNECTTHREAD_H
