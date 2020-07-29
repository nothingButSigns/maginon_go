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
    Q_PROPERTY(quint8 luminosityVal READ luminosityVal NOTIFY luminosityValChanged)
    Q_PROPERTY(quint8 RGBLuminosityVal READ RGBLuminosityVal NOTIFY rgbLuminosityValChanged)
    Q_PROPERTY(bool rgbOn READ rgbOn NOTIFY rgbEnabled)
    Q_PROPERTY(bool panelFrozen READ panelFrozen WRITE setPanel)
    Q_PROPERTY(quint8 colorCode READ colorCode NOTIFY colorCodeChanged)


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
        WRITE_ERROR = 4,
        READ_ERROR = 5,
        WRITE_SUCCESS = 6,
        READ_SUCCESS = 7
    };
    Q_ENUM(_ActionState)

    enum _ColorCodes {
        YELLOW_2 = 0xc5e100,
        PURPLE = 0x15001e,
        BLUE = 0x0700e1,
        AQUA = 0x00c9e1,
        LIME = 0xe1d800,
        OCHRE = 0xe18b00,
        GREEN_2 = 0x0ce100,
        WHITE = 0xffffff,
        MAGENTA = 0xe100c1,
        RED = 0x1e0100,
        YELLOW_1 = 0xffe500,
        GREEN_1 = 0x24ff00,
        REDDISH = 0xff0000,
    };

    Q_INVOKABLE void turnOnOff();
    Q_INVOKABLE void changeLuminosity(quint8 newLum);
    Q_INVOKABLE void changeRGBLuminosity(quint8 newLum);
    Q_INVOKABLE void switchToRGB();
    Q_INVOKABLE void switchToWhite();
    Q_INVOKABLE void setRGBColor(quint8 colorIndex);


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
    quint8 luminosityVal();
    quint8 RGBLuminosityVal();
    bool rgbOn();
    bool panelFrozen();
    void setPanel(bool mode);
    quint8 colorCode();

    void setActionState(int aState);

Q_SIGNALS:
    void bulbNameChanged();
    void bulbAddressChanged();
    void actionStateChanged();
    void bulbStateChanged();
    void luminosityValChanged();
    void rgbLuminosityValChanged();
    void rgbEnabled();
    void colorCodeChanged();


private:
    QBluetoothDeviceInfo device;
    Device *d;

    _ActionState ActionState;
    _BulbState BulbState;
    Luminosity luminosity = UNKNOWN;
    LuminosityRGB luminosityRGB = R_UNKNOWN;
    quint32 colorValue;


    bool rgbMode = false;
    bool controlPanelFrozen = false;
    quint8 colorSliderCode;


};

#endif // DEVICE_H
