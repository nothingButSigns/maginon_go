#ifndef DEVICE_H
#define DEVICE_H

#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QAbstractListModel>
#include <QObject>
#include <QDebug>

#include "actuators.h"
#include "maginon.h"

class Device: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bulbName READ bulbName NOTIFY bulbNameChanged)
    Q_PROPERTY(QString bulbAddress READ bulbAddress NOTIFY bulbAddressChanged)
    Q_PROPERTY(int actionState READ actionState WRITE setActionState NOTIFY actionStateChanged)
    // Q_PROPERTY(bool bulbState READ bulbState NOTIFY bulbStateChanged)

public:

    enum Luminosity {
        MIN_LUM = 0x22,
        LUM1 = 0x32,
        LUM2 = 0x62,
        LUM3 = 0x92,
        MAX_LUM  = 0xb2
    };

    enum LuminosityRGB {
        RMIN_LUM = 0x20
    };

    enum State {
        OFF,
        ON
    };

    enum _ActionState {
        READ_ERROR,
        WRITE_ERROR,
        WRITE_SUCCESS,
        READ_SUCCESS
    }ActionState;
    Q_ENUM(_ActionState)


    Device() = default;
    Device(const QBluetoothDeviceInfo &d);
    ~Device();
    QBluetoothDeviceInfo getDevice();
    void getInitialState();
    void retriveStateData(uint8_t* stateData);

    QString bulbName();
    QString bulbAddress();
    int actionState();
   // bool bulbState();
    void setActionState(int aState);

Q_SIGNALS:
    void bulbNameChanged();
    void bulbAddressChanged();
    void actionStateChanged();
   // void bulbStateChanged();


private:
    QBluetoothDeviceInfo device;

    State bulbState;
    Luminosity luminosity;
    LuminosityRGB luminosityRGB;
    QByteArray RGBcolor;


};

#endif // DEVICE_H
