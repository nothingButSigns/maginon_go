QT += quick
QT += quick bluetooth

CONFIG += c++11

LIBS += `pkg-config --cflags --libs glib-2.0`


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        connectthread.cpp \
        device.cpp \
        lightbulb.cpp \
        main.cpp \
        actuators.cpp \
        attrib/att_attrib.c \
        attrib/gatt.c \
        attrib/gattrib.c \
        attrib/gatttool.c \
        attrib/utils.c \
        btio.c \
        lib/bluetooth.c \
        lib/hci.c \
        lib/sdp.c \
        lib/uuid.c \
        log.c \
        shared/att.c \
        shared/crypto.c \
        shared/io-glib.c \
        shared/queue.c \
        shared/timeout-glib.c \
        shared/util.c

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += \
    ../../bluez/ \
    ../../bluez/lib/bluetooth/ \
    ../../bluez/lib/ \
    ../../bluez/btio/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    connectthread.h \
    device.h \
    lightbulb.h \
    maginon.h \
    actuators.h \
    attrib/att-database.h \
    attrib/att_attrib.h \
    attrib/gatt.h \
    attrib/gattrib.h \
    attrib/gatttool.h \
    btio.h \
    lib/bluetooth.h \
    lib/hci.h \
    lib/hci_lib.h \
    lib/l2cap.h \
    lib/rfcomm.h \
    lib/sco.h \
    lib/sdp.h \
    lib/sdp_lib.h \
    lib/uuid.h \
    log.h \
    shared/att.h \
    shared/crypto.h \
    shared/io.h \
    shared/queue.h \
    shared/timeout.h \
    shared/util.h

