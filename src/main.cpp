#include "stimeline.h"
#include "ssettings.h"

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

    if (settings.autoLoadLastFile) {
        qCInfo(smain) << "Automatically loading last saved file:"
                      << settings.lastOpenFilePath;
        timeline.load(settings.lastOpenFilePath);
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Timeline", &timeline);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
