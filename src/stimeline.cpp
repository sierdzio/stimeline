#include "stimeline.h"
#include "scalendar.h"
#include "seventdb.h"
#include "tags.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

Q_LOGGING_CATEGORY(stimeline, "STimeline")

STimeline::STimeline(QObject *parent) : QObject (parent)
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

    QFile file(path);

    if (file.exists() == false) {
        reportError("File does not exist: " + path);
        return;
    }

    if (file.open(QFile::ReadOnly | QFile::Text) == false) {
        reportError("Could not open file for reading: " + path);
        return;
    }

    // TODO: add support for binary JSON saving and loading
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));

    if (doc.isEmpty() || doc.isNull() || doc.isArray()) {
        reportError("Invalid JSON file, could not read. Path: " + path);
        return;
    }

    QJsonObject mainObj(doc.object());
    //mCalendar->fromJson(mainObj.value(Tags::calendar).toObject()); // TODO: plug in calendar::fromJson()
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

    //mainObj.insert(Tags::calendar, mCalendar->toJson());
    mainObj.insert(Tags::events, mEventDB->toJson());
    // TODO: plug in all other objects

    // TODO: check if all data was written successfully
    file.write(QJsonDocument(mainObj).toJson(QJsonDocument::Indented));
    file.close();
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
