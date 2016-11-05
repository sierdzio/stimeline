#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "stimeline.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setApplicationVersion("0.1");
    app.setApplicationDisplayName("sTimeline");
    app.setApplicationName("sTimeline");
    app.setOrganizationName("sierdzio");
    app.setOrganizationName("sierdzio"); // TODO: proper domain
    app.setQuitOnLastWindowClosed(true);

    // Just a quick test
    STimeline timeline;
    timeline.load("input.json");
    timeline.save("test.json");
    // EO Test

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
