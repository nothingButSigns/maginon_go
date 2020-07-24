#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H
#include <QThread>
#include "actuators.h"


class connectThread: public QThread
{
    Q_OBJECT
    void run() override {
        connectToBulb();

    }

public:
    connectThread();
};

#endif // CONNECTTHREAD_H
