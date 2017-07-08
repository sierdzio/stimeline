#include "stimeline.h"
#include "scalendar.h"
#include "sobjectmodel.h"
#include "sobjectsortproxymodel.h"
#include "ssettings.h"
#include "sassistant.h"
#include "ssave.h"
#include "tags.h"
#include "sobjecttags.h"

#include "quazip.h"
#include "quazipfile.h"
#include "JlCompress.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include <QStandardPaths>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniObject>
#endif

Q_LOGGING_CATEGORY(stimeline, "STimeline")

/*!
 * \class STimeline
 *
 * Main class of the application, serves as the router between C++ and QML,
 * manages current timeline, allows file saving and loading.
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
    qRegisterMetaType<SObjectTags*>();
    qRegisterMetaType<SObject>();
    qRegisterMetaType<SDateTime>();

    init();

    if (settings->autoLoadLastFile()) {
        qCInfo(stimeline) << "Automatically loading last saved file:"
                          << settings->lastOpenFilePath();
        load(settings->lastOpenFilePath());
    }
}

/*!
 * If autoSaveOnExit is true, the destructor saves the timeline to predefined
 * file.
 */
STimeline::~STimeline()
{
    if (mSettings->autoSaveOnExit()) {
        qCInfo(stimeline) << "Automatically saving current timeline to file:"
                          << mSettings->lastOpenFilePath();
        save(mSettings->lastOpenFilePath());
    }
}

/*!
 * Clears current timeline, all objects and calendars
 */
void STimeline::clear()
{
    mSettings->setName(QString::null);

    //QString mRuntimeDataPath;
    //QVector<QByteArray> mPictureCache;
    //SCalendar *mCalendar = nullptr;
    mEventModel->clear();
    mPersonModel->clear();
    mArtifactModel->clear();
    mPlaceModel->clear();
    mMapModel->clear();
    mTags->clear();

    mEventModelProxy->sort(0);
}

/*!
 * Loads the whole timeline from a file under \a path.
 */
void STimeline::load(const QString &path)
{
    const QString parsedPath(SAssistant::cleanPath(path));

    SSave load;
    if (!load.load(path)) {
        return;
    }

    if (mSettings) {
        mSettings->setLastOpenFilePath(parsedPath);
    }

    mPictureCache = load.pictureCache();
    mRuntimeDataPath = load.runtimeDataPath();

    QJsonObject mainObj(load.json());
    mSettings->setAuthor(mainObj.value(Tags::author).toString());

    mCalendar->fromJson(mainObj.value(Tags::calendar).toArray());
    mEventModel->fromJson(mainObj.value(Tags::events).toArray());
    mPersonModel->fromJson(mainObj.value(Tags::people).toArray());
    mArtifactModel->fromJson(mainObj.value(Tags::artifacts).toArray());
    mPlaceModel->fromJson(mainObj.value(Tags::places).toArray());
    mMapModel->fromJson(mainObj.value(Tags::maps).toArray());
    mTags->fromJson(mainObj.value(Tags::tags).toArray());

    mEventModelProxy->sort(0);
}

/*!
 * Saves current timeline data to a file under \a path.
 */
void STimeline::save(const QString &path) const
{
    const QString parsedPath(SAssistant::cleanPath(path));

    QJsonObject mainObj;

    // Add metadata
    mainObj.insert(Tags::version, QCoreApplication::applicationVersion());
    mainObj.insert(Tags::timestamp, QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    mainObj.insert(Tags::author, mSettings->author());

    mainObj.insert(Tags::calendar, mCalendar->toJson());
    mainObj.insert(Tags::events, mEventModel->toJson());
    mainObj.insert(Tags::people, mPersonModel->toJson());
    mainObj.insert(Tags::artifacts, mArtifactModel->toJson());
    mainObj.insert(Tags::places, mPlaceModel->toJson());
    mainObj.insert(Tags::maps, mMapModel->toJson());
    mainObj.insert(Tags::tags, mTags->toJson());

    SSave save(mRuntimeDataPath);
    save.setJson(mainObj);

    if (!save.save(parsedPath)) {
        // TODO: fix. Why save() returns false on Android?
        qDebug(stimeline) << "Save not successful?";
        return;
    }

    if (mSettings) {
        mSettings->setLastOpenFilePath(parsedPath);
    }
}

/*!
 * Creates a temporary sTimeline archive (.tmln) and "exports" it. Meaning:
 * on Android the file will be sent via Intent. You can then choose with which
 * app to work on it further (send by mail, save on disk, share via messenger
 * and so on).
 */
void STimeline::exportSave() const
{
#ifdef Q_OS_ANDROID
    const QString path(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                       + "/" + mSettings->name());
    QAndroidJniObject string = QAndroidJniObject::fromString(path);
    QtAndroid::androidActivity().callMethod<void>("save", "(Ljava/lang/String;)V",
                                                  string.object<jstring>());
    qDebug(stimeline) << "After JNI";
#endif
}

/*!
 * Load calendar definition from \a path file. The file can be just calendar
 * definition or full sTimeline save file - only calendar will be extracted
 * from it.
 *
 * \a path can also point to compressed timeline file.
 */
void STimeline::loadCalendar(const QString &path)
{
    const QString parsedPath(SAssistant::cleanPath(path));

    SSave load;
    if (!load.load(path)) {
        return;
    }

    const QJsonObject object(load.json());
    const QJsonArray calendar(object.value(Tags::calendar).toArray());
    mCalendar->fromJson(calendar);
}

/*!
 * Saves current calendar definition to file \a path. File will be saved as
 * uncompressed JSON.
 */
void STimeline::saveCalendar(const QString &path) const
{
    QJsonObject object;
    object.insert(Tags::calendar, mCalendar->toJson());

    SSave save(mRuntimeDataPath);
    save.setJson(object);

    if (!save.save(path)) {
        qDebug(stimeline) << "Could not save calendar";
        return;
    }
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
 * cache/ deduplicated storage.
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
    return mRuntimeDataPath + QStringLiteral("/") + Tags::picturesDir;
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

void STimeline::addTag(SObject object, const QString &tag)
{
    const uint id = mTags->addTag(tag);
    if (!object.mTags.contains(id)) {
        object.mTags.append(id);
        model(int(object.mType))->updateObject(object);
    }

    qDebug() << "Add tag" << id << tag;
}

void STimeline::removeTag(SObject object, const uint id)
{
    mTags->removeTag(id);
    if (!object.mTags.removeOne(id))
        qDebug() << "Tag not removed from object.";
    model(int(object.mType))->updateObject(object);

    qDebug() << "Remove tag" << id;
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
    mTags = new SObjectTags(this);
}
