#include "stimeline.h"
#include "ssettings.h"
#include "sqmlassistant.h"

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
    SQmlAssistant assistant;
    STimeline timeline(&settings);

    if (settings.autoLoadLastFile) {
        qCInfo(smain) << "Automatically loading last saved file:"
                      << settings.lastOpenFilePath;
        timeline.load(settings.lastOpenFilePath);
    }

    qmlRegisterSingletonType<SQmlAssistant>("Assistant", 1, 0, "Assistant",
                                            SQmlAssistant::assistantSingletonProvider);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Timeline", &timeline);
    engine.rootContext()->setContextProperty("Assistant", &assistant); // TODO: QML singleton?
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
