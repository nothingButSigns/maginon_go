#include "lightbulb.h"
#include "connectionthread.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Lightbulb lb;

    qmlRegisterType<ConnectionThread>("myLib", 1, 0, "ConnectionThread");
    qmlRegisterType<Device>("currentDevice", 1, 0, "Device");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("Lightbulb", &lb);

    lb.searchForDevices();

    engine.load(url);

    return app.exec();
}
