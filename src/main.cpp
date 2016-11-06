#include "stimeline.h"
#include "sdatetime.h"
#include "ssettings.h"
#include "seventptr.h"
#include "sevent.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(smain)
Q_LOGGING_CATEGORY(smain, "Main")

Q_DECLARE_METATYPE(SEventPtr)
Q_DECLARE_METATYPE(SEventVector)

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

    qRegisterMetaType<SDateTime>();
    qRegisterMetaType<SEvent*>();
    qRegisterMetaType<SEventPtr>();
    qRegisterMetaType<SEventVector>();
    SSettings settings;
    STimeline timeline(&settings);

    if (settings.autoLoadLastFile) {
        qCInfo(smain) << "Automatically loading last saved file:"
                      << settings.lastOpenFilePath;
        timeline.load(settings.lastOpenFilePath);
    }

    // Just a quick test
    //timeline.load("input.json");
    //timeline.save("test.json");
    // EO Test

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Timeline", &timeline);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
