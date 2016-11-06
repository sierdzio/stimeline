#include "stimeline.h"
#include "scalendar.h"
#include "seventdb.h"
#include "sevent.h"
#include "ssettings.h"
#include "tags.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

Q_LOGGING_CATEGORY(stimeline, "STimeline")

STimeline::STimeline(SSettings *settings, QObject *parent) : QObject (parent),
    mSettings(settings)
{
    init();
}

void STimeline::load(const QString &path)
{
    // Clear previous state
    //bool reinit = false;
    //if (mCalendar.isNull() == false) { mCalendar.clear(); reinit = true; }
    //if (mEventDB.isNull() == false) { mEventDB.clear(); reinit = true; }

    //if (reinit)
    //    init();

    QString parsedPath(path);
    if (parsedPath.startsWith("file://")) {
        parsedPath = path.mid(7);
    }

    QFile file(parsedPath);

    if (file.exists() == false) {
        reportError("File does not exist: " + parsedPath);
        return;
    }

    if (file.open(QFile::ReadOnly | QFile::Text) == false) {
        reportError("Could not open file for reading: " + parsedPath);
        return;
    }

    // TODO: add support for binary JSON saving and loading
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));

    if (doc.isEmpty() || doc.isNull() || doc.isArray()) {
        reportError("Invalid JSON file, could not read. Path: " + parsedPath);
        return;
    }

    if (mSettings) {
        mSettings->lastOpenFilePath = parsedPath;
    }

    QJsonObject mainObj(doc.object());
    mCalendar->fromJson(mainObj.value(Tags::calendar).toArray());
    mEventDB->fromJson(mainObj.value(Tags::events).toArray());
    // TODO: plug in all other objects
}

void STimeline::save(const QString &path) const
{
    QFile file(path);

    if (file.open(QFile::WriteOnly | QFile::Text) == false) {
        reportError("Could not open file for saving: " + path);
        return;
    }

    QJsonObject mainObj;

    // Add metadata
    mainObj.insert(Tags::version, QCoreApplication::applicationVersion());
    mainObj.insert(Tags::timestamp, QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    mainObj.insert(Tags::author, "Testing Tom"); // TODO: plug in author from app settings

    mainObj.insert(Tags::calendar, mCalendar->toJson());
    mainObj.insert(Tags::events, mEventDB->toJson());
    // TODO: plug in all other objects

    // TODO: check if all data was written successfully
    const QByteArray data(QJsonDocument(mainObj).toJson(QJsonDocument::Indented));
    const qint64 bytesWritten = file.write(data);
    if (bytesWritten != data.size()) {
        qCDebug(stimeline) << "File saving: something went wrong. Data size:"
                           << data.size() << "Bytes written:" << bytesWritten;
    }
    file.close();
}

SEvent* STimeline::events() const
{
//    QString result;

//    const SEventVector events = mEventDB->events();
//    for (const SEventPtr &event: events) {
//        result.append("Event: " + event->(Tags::id) + ", name: "
//                      + event->property(Tags::name) + ", description: "
//                      + event->property(Tags::description));
//    }

//    return result;
    const SEventVector events(mEventDB->events());
    qDebug() << events.first()->id();
    return /*events.isEmpty()? new SEvent : */events.first().data();
}

void STimeline::init()
{
    qCDebug(stimeline) << "Initializing default timeline...";
    mCalendar = QSharedPointer<SCalendar>::create();
    mEventDB = QSharedPointer<SEventDB>::create();
}

void STimeline::reportError(const QString &message) const
{
    qCDebug(stimeline) << message;
    emit error(message);
}
