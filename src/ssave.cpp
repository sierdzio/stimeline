#include "ssave.h"
#include "sassistant.h"
#include "tags.h"

#include "quazip.h"
#include "quazipfile.h"
#include "JlCompress.h"

#include <QJsonDocument>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(ssave, "SSave")

/*!
 * \class SSave
 * \brief Manages operations on saved files: saving, loading. Automatically
 * detects save file type (compressed save or uncompressed save).
 *
 * Uncompressed saves look like this:
 *
 \verbatim
 --savedFileName.json
 --pictures/
  |
  ---cachedPicture.png
  |
  ---cachedPicture2.jpg
 \endverbatim
 *
 * No data is compressed, so both JSON file and "pictures" directory are freely
 * available on the file system. You can look them up (and edit!) using any tools
 * from your Operating System.
 *
 * When you save an uncompressed file, the JSON file is overwritten, and picture
 * cache is updated (not replaces).
 *
 * To see a description of picture cache, see STimeline::loadPicture().
 *
 * Compressed saves (.tmln) take all the data of an uncompressed save, and put
 * them into a single ZIP archive with .tmln extension. You can access and
 * modify the ZIP using any archiving tool, sTimeline app will not mind.
 *
 * Once opened, a compressed save is extracted into a TEMP directory (exact
 * location depends on your Operating System. You can check the path in sTimeline
 * logs). While the application is running, that temp location is used as if the
 * save was not compressed at all. Once you choose to save it again (or use
 * autosave feature), the temp data is compressed into a single .tmln file and
 * copied to location of your choosing.
 */

/*!
 * Default constructor. \a runtimeDataPath is optional. Provide it if you don't
 * want sTimeline to use a randomized temp location.
 *
 * \sa runtimeDataPath
 */
SSave::SSave(const QString &runtimeDataPath) : mRuntimeDataPath(runtimeDataPath)
{
    if (mRuntimeDataPath.isEmpty())
        mRuntimeDataPath = generateRuntimePath();
}

/*!
 * Returns the data path - that is the directory where temporary save file data
 * is being stored.
 */
QString SSave::runtimeDataPath() const
{
    return mRuntimeDataPath;
}

/*!
 * Generic loading routine, returns true on successful load. SSave automatically
 * detects whether \a path is compressed or not and extracts the data.
 *
 * After loading, JSON data is available through json(), picture cache list is
 * under pictureCache(), and the location of JSON file and pictures is available
 * from runtimeDataPath().
 *
 * \sa json, pictureCache, runtimeDataPath
 */
bool SSave::load(const QString &path)
{
    init();
    const QString parsedPath(SAssistant::cleanPath(path));
    const QFileInfo file(parsedPath);
    mLoadDataPath = parsedPath;

    if (file.suffix() == Tags::extensionUncompressed) {
        return loadUncompressed(parsedPath);
    } else if (file.suffix() == Tags::extensionCompressed) {
        return loadCompressed(parsedPath);
    }

    reportError("Wrong file extension: " + parsedPath);
    return false;
}

/*!
 * Generic saving routine, returns true on successful save. SSave automatically
 * detects whether \a path is compressed or not and either saves the data
 * directly or creates a compressed save.
 */
bool SSave::save(const QString &path)
{
    init();
    const QString parsedPath(SAssistant::cleanPath(path));
    const QFileInfo file(parsedPath);
    mSaveDataPath = parsedPath;

    if (file.suffix() == Tags::extensionUncompressed) {
        return saveUncompressed(parsedPath);
    } else if (file.suffix() == Tags::extensionCompressed) {
        return saveCompressed(parsedPath);
    }

    reportError("Wrong file extension: " + parsedPath);
    return false;
}

/*!
 * Returns the JSON object containing all the timeline data.
 */
QJsonObject SSave::json() const
{
    return mJson;
}

/*!
 * Set the \a json object containing all the timeline data. Use this function
 * before calling save().
 */
void SSave::setJson(const QJsonObject &json)
{
    mJson = json;
}

/*!
 * Returns the list of picture checksums - used to facilitate picture caching.
 */
QVector<QByteArray> SSave::pictureCache() const
{
    return mPictureCache;
}

/*!
 * \internal
 *
 * Initializes the SSave object. Warning: SSave should be used once only and
 * then discarded.
 */
void SSave::init()
{
    mIsError = false;
    //mSaveDataPath.clear();
    //mLoadDataPath.clear();
    //mPictureCache.clear();
    //mJson = QJsonObject();
}

/*!
 * Loads a compressed save file from \a path. Returns true on success.
 */
bool SSave::loadCompressed(const QString &path)
{
    const QString tempLoadPath(generateRuntimePath());
    qDebug(ssave) << "Loading compressed to temp path:" << tempLoadPath;

    if (JlCompress::extractDir(path, tempLoadPath).isEmpty()) {
        reportError("Could not extract file: " + path + "into: " + tempLoadPath);
        return false;
    }

    const QFileInfo file(path);
    return loadUncompressed(tempLoadPath + "/" + file.baseName()
                            + "." + Tags::extensionUncompressed);
}

/*!
 * Loads uncompressed file data from \a path. The \a path should point to .json
 * file. Returns true on success.
 */
bool SSave::loadUncompressed(const QString &path)
{
    if (!loadJson(path)) {
        return false;
    }

    if (!loadPictures(path)) {
        return false;
    }

    mRuntimeDataPath = QFileInfo(path).absolutePath();

    return true;
}

/*!
 * Loads the JSON data from \a path. Returns true on success.
 */
bool SSave::loadJson(const QString &path)
{
    QFile file(path);

    if (file.exists() == false) {
        reportError("File does not exist: " + path);
        return false;
    }

    if (file.open(QFile::ReadOnly | QFile::Text) == false) {
        reportError("Could not open file for reading: " + path);
        return false;
    }

    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));

    if (doc.isEmpty() || doc.isNull() || doc.isArray()) {
        reportError("Invalid JSON file, could not read. Path: " + path);
        return false;
    }

    mJson = doc.object();
    return true;
}

/*!
 * Loads pictures from \a path + /pictures/. Builds the picture cache. Returns
 * true on success.
 */
bool SSave::loadPictures(const QString &path)
{
    const QFileInfo json(path);
    const QDir picDir(json.absolutePath() + "/" + Tags::picturesDir);
    const QFileInfoList pics(picDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot));

    for (auto pic: pics) {
        mPictureCache.append(pic.baseName().toLatin1());
    }

    return true;
}

/*!
 * Creates a compressed timeline archive and puts it in \a path. Returns true on
 * success.
 */
bool SSave::saveCompressed(const QString &path)
{
    const QFileInfo file(path);
    const QString tempSavePath(generateRuntimePath() + "/" + file.baseName()
                               + "." + Tags::extensionUncompressed);
    qDebug(ssave) << "Using temp save path:" << tempSavePath;

    const QDir baseDir(QFileInfo(tempSavePath).absoluteDir());
    qDebug(ssave) << "Creating temp path:" << baseDir.absolutePath()
                  << "from:" << baseDir.absolutePath()
                  << "exists?" << baseDir.exists();
    if (!baseDir.exists()) {
        if (!baseDir.mkpath(baseDir.absolutePath())) {
            reportError("Could not create temp dir: " + baseDir.absolutePath());
            return false;
        }
    }

    if (!saveUncompressed(tempSavePath)) {
        return false;
    }

    if (!JlCompress::compressDir(path, baseDir.absolutePath(), true)) {
        reportError("Compression error. Input: " + tempSavePath + ", output: "
                    + path);
    }

    return false;
}

/*!
 * Creates an uncompressed timeline archive and puts it in \a path. Returns true
 * on success.
 */
bool SSave::saveUncompressed(const QString &path)
{
    qDebug(ssave) << "Saving uncompressed to:" << path;

    if (!saveJson(path)) {
        return false;
    }

    if (!savePictures(path)) {
        return false;
    }

    return true;
}

/*!
 * Saves JSON file to \a path and returns true on success.
 */
bool SSave::saveJson(const QString &path)
{
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Text) == false) {
        reportError("Could not open file for saving: " + path);
        return false;
    }

    // TODO: check if all data was written successfully
    const QByteArray data(QJsonDocument(mJson).toJson(QJsonDocument::Indented));
    const qint64 bytesWritten = file.write(data);
    if (bytesWritten != data.size()) {
        // TODO: use reportError()
        qCDebug(ssave) << "File saving: something went wrong. Data size:"
                       << data.size() << "Bytes written:" << bytesWritten;
        return false;
    }

    return true;
}

/*!
 * Saves all pictures from cache into \a path + /pictures/. Returns true on
 * success.
 *
 * If pictures dir does not exist, this method will try to create it.
 */
bool SSave::savePictures(const QString &path)
{
    // Write all pictures
    QDir pictureDir(QFileInfo(path).absoluteDir());
    if (!pictureDir.exists(Tags::picturesDir)) {
        pictureDir.mkdir(Tags::picturesDir);
    }
    pictureDir.cd(Tags::picturesDir);

    const QStringList existingPics(pictureDir.entryList(QDir::Files | QDir::NoDotAndDotDot));
    const QString basePicturePath(mRuntimeDataPath + "/" + Tags::picturesDir);
    const QFileInfoList sourcePics(QDir(basePicturePath).entryInfoList(QDir::Files | QDir::NoDotAndDotDot));
    for (auto pic: sourcePics) {
        if (!existingPics.contains(pic.fileName())) {
            QFile::copy(basePicturePath + "/" + pic.fileName(),
                        pictureDir.absolutePath() + "/" + pic.fileName());
        }
    }

    return true;
}

/*!
 * Returns a temporary location (writable) to use for storing runtime artifacts
 * (picture cache, JSON file for saving pusposes, extracted compressed save data,
 * and so on).
 */
QString SSave::generateRuntimePath() const
{
    return QStandardPaths::writableLocation(QStandardPaths::TempLocation)
            + "/sTimeline-" + SAssistant::generateId().left(10);
}

/*!
 * Convenience method. Prints \a message and emits an error() signal.
 */
void SSave::reportError(const QString &message)
{
    mIsError = true;
    qCDebug(ssave) << message;
    //    emit error(message);
}
