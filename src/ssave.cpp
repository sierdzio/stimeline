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

SSave::SSave(const QString &runtimeDataPath) : mRuntimeDataPath(runtimeDataPath)
{
    if (mRuntimeDataPath.isEmpty())
        mRuntimeDataPath = generateRuntimePath();
}

QString SSave::runtimeDataPath() const
{
    return mRuntimeDataPath;
}

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

QJsonObject SSave::json() const
{
    return mJson;
}

void SSave::setJson(const QJsonObject &json)
{
    mJson = json;
}

QVector<QByteArray> SSave::pictureCache() const
{
    return mPictureCache;
}

void SSave::init()
{
    mIsError = false;
    //mSaveDataPath.clear();
    //mLoadDataPath.clear();
    //mPictureCache.clear();
    //mJson = QJsonObject();
}

bool SSave::loadCompressed(const QString &path)
{
    // TODO: implement!
    Q_UNUSED(path);
    return false;
}

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

bool SSave::saveCompressed(const QString &path)
{
    Q_UNUSED(path);

    // STM test!
    // TODO: only compress STimelinefiles, do not include any other files found
    // in outDirPath
    //JlCompress::compressDir(outDirPath + "/testZip.zip", outDirPath);

    return false;
}

bool SSave::saveUncompressed(const QString &path)
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
    file.close();

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
            + "/sTimeline" + SAssistant::generateId();
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
