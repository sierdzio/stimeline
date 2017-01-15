#include "stimeline.h"
#include "scalendar.h"
#include "sobjectmodel.h"
#include "sobjectsortproxymodel.h"
#include "ssettings.h"
#include "sassistant.h"
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
    qRegisterMetaType<SObjectSortProxyModel*>();
    qRegisterMetaType<SObjectModel*>();
    qRegisterMetaType<SSettings*>();
    qRegisterMetaType<SCalendar*>();
    qRegisterMetaType<STimeline*>();
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
    const QString parsedPath(SAssistant::cleanPath(path));
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
    mSettings->author = mainObj.value(Tags::author).toString();

    mCalendar->fromJson(mainObj.value(Tags::calendar).toArray());
    mEventModel->fromJson(mainObj.value(Tags::events).toArray());
    mPersonModel->fromJson(mainObj.value(Tags::people).toArray());
    mArtifactModel->fromJson(mainObj.value(Tags::artifacts).toArray());
    mPlaceModel->fromJson(mainObj.value(Tags::places).toArray());
    mMapModel->fromJson(mainObj.value(Tags::maps).toArray());

    mEventModelProxy->sort(0);
}

void STimeline::save(const QString &path) const
{
    QString parsedPath(SAssistant::cleanPath(path));
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
    mainObj.insert(Tags::people, mPersonModel->toJson());
    mainObj.insert(Tags::artifacts, mArtifactModel->toJson());
    mainObj.insert(Tags::places, mPlaceModel->toJson());
    mainObj.insert(Tags::maps, mMapModel->toJson());

    // TODO: check if all data was written successfully
    const QByteArray data(QJsonDocument(mainObj).toJson(QJsonDocument::Indented));
    const qint64 bytesWritten = file.write(data);
    if (bytesWritten != data.size()) {
        qCDebug(stimeline) << "File saving: something went wrong. Data size:"
                           << data.size() << "Bytes written:" << bytesWritten;
    }
    file.close();
}

SObjectModel *STimeline::model(const QString &type) const
{
    return model(int(SObject::stringToType(type)));
}

SObjectModel *STimeline::model(const int type) const
{
    auto typeEnum = SObject::ObjectType(type);

    if (typeEnum == SObject::ObjectType::Event) {
        return mEventModel;
    } else if (typeEnum == SObject::ObjectType::Person) {
        return mPersonModel;
    } else if (typeEnum == SObject::ObjectType::Artifact) {
        return mArtifactModel;
    } else if (typeEnum == SObject::ObjectType::Place) {
        return mPlaceModel;
    } else if (typeEnum == SObject::ObjectType::Map) {
        return mMapModel;
    } else {
        qDebug(stimeline) << "Model not found for type" << type
                          << SObject::typeToString(typeEnum);
        return nullptr;
    }
}

void STimeline::init()
{
    qCDebug(stimeline) << "Initializing default timeline...";
    mCalendar = new SCalendar(this);
    mEventModel = new SObjectModel(this);
    mEventModelProxy = new SObjectSortProxyModel(this);
    mEventModelProxy->setSourceModel(mEventModel);
    mEventModelProxy->sort(0);
    mPersonModel = new SObjectModel(this);
    mArtifactModel = new SObjectModel(this);
    mPlaceModel = new SObjectModel(this);
    mMapModel = new SObjectModel(this);
}

void STimeline::reportError(const QString &message) const
{
    qCDebug(stimeline) << message;
    emit error(message);
}
