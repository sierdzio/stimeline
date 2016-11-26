#include "stimeline.h"
#include "ssettings.h"
#include "sqmlassistant.h"
#include "customItems/eventtimeline.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(smain)
Q_LOGGING_CATEGORY(smain, "Main")

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

    SSettings settings;
    STimeline timeline(&settings);

    qmlRegisterSingletonType<SQmlAssistant>("Assistant", 1, 0, "Assistant",
                                            SQmlAssistant::assistantSingletonProvider);
    qmlRegisterType<EventTimeline>("CustomItems", 1, 0, EventTimeline::staticMetaObject.className());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Timeline", &timeline);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
