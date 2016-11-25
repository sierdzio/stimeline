#include "stimeline.h"
#include "scalendar.h"
#include "seventmodel.h"
#include "ssettings.h"
#include "tags.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

Q_LOGGING_CATEGORY(stimeline, "STimeline")

STimeline::STimeline(SSettings *settings, QObject *parent) : QObject (parent),
    mSettings(settings)
{
    qRegisterMetaType<SEventModel*>();
    qRegisterMetaType<SSettings*>();
    qRegisterMetaType<SCalendar*>();
    init();

    if (settings->autoLoadLastFile) {
        qCInfo(stimeline) << "Automatically loading last saved file:"
                          << settings->lastOpenFilePath;
        load(settings->lastOpenFilePath);
    }
}

STimeline::~STimeline()
{
    if (mSettings->autoSaveOnExit) {
        qCInfo(stimeline) << "Automatically saving current timeline to file:"
                          << mSettings->lastOpenFilePath;
        save(mSettings->lastOpenFilePath);
    }
}

void STimeline::load(const QString &path)
{
    // Clear previous state
    //bool reinit = false;
    //if (mCalendar.isNull() == false) { mCalendar.clear(); reinit = true; }
    //if (mEventDB.isNull() == false) { mEventDB.clear(); reinit = true; }

    //if (reinit)
    //    init();

    const QString parsedPath(cleanPath(path));
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
    mEventModel->fromJson(mainObj.value(Tags::events).toArray());
    mSettings->author = mainObj.value(Tags::author).toString();
    // TODO: plug in all other objects
}

void STimeline::save(const QString &path) const
{
    QString parsedPath(cleanPath(path));
    QFile file(parsedPath);

    if (file.open(QFile::WriteOnly | QFile::Text) == false) {
        reportError("Could not open file for saving: " + parsedPath);
        return;
    }

    QJsonObject mainObj;

    // Add metadata
    mainObj.insert(Tags::version, QCoreApplication::applicationVersion());
    mainObj.insert(Tags::timestamp, QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    mainObj.insert(Tags::author, mSettings->author); // TODO: plug in author from app settings

    mainObj.insert(Tags::calendar, mCalendar->toJson());
    mainObj.insert(Tags::events, mEventModel->toJson());
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

void STimeline::init()
{
    qCDebug(stimeline) << "Initializing default timeline...";
    mCalendar = new SCalendar(this);
    mEventModel = new SEventModel(this);
}

void STimeline::reportError(const QString &message) const
{
    qCDebug(stimeline) << message;
    emit error(message);
}

QString STimeline::cleanPath(const QString &urlPath) const
{
    const QLatin1String fileUrl("file://");
    if (urlPath.startsWith(fileUrl)) {
        return urlPath.mid(fileUrl.size());
    }

    return urlPath;
}
