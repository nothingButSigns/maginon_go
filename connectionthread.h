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
    Q_PROPERTY(QString randomString READ randomString WRITE setRandomString NOTIFY randomStringChanged)

    void run() override {
        connectToBulb(this);
    }

public:
    connectionThread(){};

    state connectionState();
    QString randomString();
    void setConnectionState(state currentState);
    void setRandomString(QString newString);

Q_SIGNALS:
    void stateConnected();
    void stateConnecting();
    void stateDisconnected();
    void connectionStateChanged();
    void randomStringChanged();


private:
    state conn_state;
    QString rStr = "Random string";
};

#endif // CONNECTTHREAD_H
