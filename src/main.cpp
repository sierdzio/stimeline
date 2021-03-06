/*i
 target name sTimeline
 qt core gui qml quick quickcontrols2
 lib -lz
 includes 3rdParty/quazip/quazip
 */

#include "stimeline.h"
#include "sobject.h"
#include "ssettings.h"
#include "sassistant.h"
#include "customItems/eventtimelineview.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(smain)
Q_LOGGING_CATEGORY(smain, "Main")

//! Main routine. Fires up the QML engine
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setApplicationVersion("0.3");
    app.setApplicationDisplayName("sTimeline");
    app.setApplicationName("sTimeline");
    app.setOrganizationName("sierdzio");
    app.setOrganizationDomain("org.stimeline");
    app.setQuitOnLastWindowClosed(true);

    SSettings settings;
    STimeline timeline(&settings);

    qRegisterMetaType<SObject>();
    qmlRegisterUncreatableType<SObject>("CustomItems", 1, 0, "SObject",
                                        "You cannot instantiate SObject ion QML");
    qmlRegisterSingletonType<SAssistant>("Assistant", 1, 0, "Assistant",
                                         SAssistant::assistantSingletonProvider);
    qmlRegisterType<EventTimelineView>("CustomItems", 1, 0,
                                       EventTimelineView::staticMetaObject.className());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Timeline", &timeline);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
            return -1;

    return app.exec();
}
