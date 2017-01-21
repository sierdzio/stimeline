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
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

Q_LOGGING_CATEGORY(stimeline, "STimeline")

/*!
 * \class STimeline
 *
 * Main class of the application, serves as the router between C++ and QML,
 * manages current timeline, allows file saving and loading.
 */

/*!
 * \fn STimeline::error(const QString &message)
 *
 * Emitted on error.
 */

/*!
 * \property STimeline::eventModelProxy
 *
 * Used by QML to display events (sorted).
 */

/*!
 * \property STimeline::eventModel
 *
 * Main event model (unsorted).
 */

/*!
 * \property STimeline::personModel
 *
 * Model holding all people.
 */

/*!
 * \property STimeline::artifactModel
 *
 * Model holding all artifacts.
 */

/*!
 * \property STimeline::placeModel
 *
 * Model holding all places.
 */

/*!
 * \property STimeline::mapModel
 *
 * Model holding all maps.
 */

/*!
 * \property STimeline::settings
 *
 * Pointer to SSettings instance.
 */

/*!
 * \property STimeline::calendar
 *
 * Pinter to current calendar system in use (SCalendar).
 */

/*!
 * Constructor, requires a valid \a settings pointer and optionally a QObject
 * \a parent.
 */
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

/*!
 * If autoSaveOnExit is true, the destructor saves the timeline to predefined
 * file.
 */
STimeline::~STimeline()
{
    if (mSettings->autoSaveOnExit) {
        qCInfo(stimeline) << "Automatically saving current timeline to file:"
                          << mSettings->lastOpenFilePath;
        save(mSettings->lastOpenFilePath);
    }
}

/*!
 * Loads the whole timeline from a file under \a path.
 */
void STimeline::load(const QString &path)
{
    // TODO: add picture cache filling!
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

/*!
 * Saves current timeline data to a file under \a path.
 */
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

/*!
 * Loads a new picture from \a absolutePath into pictures directory and returns
 * the relative picture path. That path needs to be appended to basePicturePath().
 *
 * STimeline supports one picture per SObject. All pictures selected by user from
 * the hard drive are copied into pictures directory. The name of the picture is
 * changed to \<file SHA1 checksum\>.\<original extension\>. This allows us to quickly
 * recognise when a similar file is already present in pictures directory and
 * refrain from storing it again. So, the "pictures" directory acts like a simple
 * cache/ deduplication storage.
 */
QString STimeline::loadPicture(const QString &absolutePath)
{
    const QString cleanedPath(SAssistant::cleanPath(absolutePath));
    const QString basePath(basePicturePath());

    QDir pictureDir(basePath);
    if (!pictureDir.exists()) {
        pictureDir.mkpath(pictureDir.absolutePath());
    }

    const QByteArray fileHash(SAssistant::fileChecksum(cleanedPath));
    const QString result(fileHash + "." + QFileInfo(cleanedPath).suffix());

    if (!mPictureCache.contains(fileHash)) {
        // Add picture checksum to picture cache
        mPictureCache.append(fileHash);
        // Copy file to pictures dir
        if (!QFile::copy(cleanedPath, pictureDir.absolutePath() + "/" + result)) {
            qDebug(stimeline) << "Error while copying" << cleanedPath << "to"
                              << pictureDir.absolutePath() + "/" + result;
            return QString();
        }
    }

    return result;
}

/*!
 * This is where stimeline will look for pictures for SObjects. Returns an absolute
 * path to "pictures" directory.
 *
 * Pictures dir will be located in the same dir as main JSON extracted from save.
 */
QString STimeline::basePicturePath() const
{
    return QFileInfo(mSettings->lastOpenFilePath).absolutePath()
            + QStringLiteral("/pictures");
}

/*!
 * Returns the correct SObjectModel for given object \a type.
 */
SObjectModel *STimeline::model(const QString &type) const
{
    return model(int(SObject::stringToType(type)));
}

/*!
 * Returns the correct SObjectModel for given object \a type.
 */
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

/*!
 * Initializes a new STimeline object.
 */
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

/*!
 * Convenience method. Prints \a message and emits an error() signal.
 */
void STimeline::reportError(const QString &message) const
{
    qCDebug(stimeline) << message;
    emit error(message);
}
