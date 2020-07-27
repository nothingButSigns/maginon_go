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
    Q_PROPERTY(int actionState READ actionState NOTIFY actionStateChanged)
    Q_PROPERTY(bool bulbState READ bulbState NOTIFY bulbStateChanged)

public:

    enum Luminosity {
        MIN_LUM = 0x22,
        LUM1 = 0x32,
        LUM2 = 0x62,
        LUM3 = 0x92,
        MAX_LUM  = 0xb2,
        UNKNOWN = 0xee
    };
    Q_ENUM(Luminosity)

    enum LuminosityRGB {
        RLUM_MIN = 0x20,
        RLUM1 = 0x30,
        RLUM2 = 0x40,
        RLUM3 = 0x50,
        RLUM4 = 0x60,
        RLUM5 = 0x70,
        RLUM6 = 0x80,
        RLUM7 = 0x90,
        RLUM_MAX = 0xa0,
        R_UNKNOWN = 0xee
    };
    Q_ENUM(LuminosityRGB)

    enum _BulbState {
        OFF,
        ON
    };
    Q_ENUM(_BulbState)

    enum _ActionState {
        WRITE_ERROR = 3,
        READ_ERROR = 4,
        WRITE_SUCCESS = 5,
        READ_SUCCESS = 6
    };
    Q_ENUM(_ActionState)

    Q_INVOKABLE void turnOnOff();


    Device() = default;
    Device(const QBluetoothDeviceInfo &d);
    Device(const Device &d);
    ~Device();
    QBluetoothDeviceInfo getDevice();
    void getInitialState();
    void retriveStateData(uint8_t* stateData);

    QString bulbName();
    QString bulbAddress();
    int actionState();
    bool bulbState();
    void setActionState(int aState);

Q_SIGNALS:
    void bulbNameChanged();
    void bulbAddressChanged();
    void actionStateChanged();
    void bulbStateChanged();


private:
    QBluetoothDeviceInfo device;
    Device *d;

    _ActionState ActionState;
    _BulbState BulbState;
    Luminosity luminosity = UNKNOWN;
    LuminosityRGB luminosityRGB = R_UNKNOWN;
    QByteArray lightColor;


};

#endif // DEVICE_H
