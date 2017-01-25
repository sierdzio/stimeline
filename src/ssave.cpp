#include "ssave.h"
#include "sassistant.h"
#include "tags.h"

#include "quazip.h"
#include "quazipfile.h"
#include "JlCompress.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>
#include <QFileInfo>
#include <QFile>

Q_LOGGING_CATEGORY(ssave, "SSave")

SSave::SSave()
{
}

bool SSave::load(const QString &path)
{
    init();
    const QString parsedPath(SAssistant::cleanPath(path));
    const QFileInfo file(parsedPath);
    mLoadPath = parsedPath;

    if (file.suffix() == QStringLiteral(".json")) {
        return loadUncompressed(parsedPath);
    } else if (file.suffix() == QStringLiteral(".tmln")) {
        return loadCompressed(parsedPath);
    }

    reportError("Wrong file extension: " + parsedPath);
    return false;
}

bool SSave::save(const QString &path, const QString &author)
{
    init();
    const QString parsedPath(SAssistant::cleanPath(path));
    const QFileInfo file(parsedPath);
    mSavePath = parsedPath;

    if (file.suffix() == QStringLiteral(".json")) {
        return saveUncompressed(parsedPath, author);
    } else if (file.suffix() == QStringLiteral(".tmln")) {
        return saveCompressed(parsedPath, author);
    }

    reportError("Wrong file extension: " + parsedPath);
    return false;
}

QJsonObject SSave::json() const
{
    return mJson;
}

void SSave::init()
{
    mIsError = false;
    mSavePath.clear();
    mLoadPath.clear();
    mPictureCache.clear();
    mJson = QJsonObject();
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

bool SSave::saveCompressed(const QString &path, const QString &author)
{
    // STM test!
    // TODO: only compress STimelinefiles, do not include any other files found
    // in outDirPath
    //JlCompress::compressDir(outDirPath + "/testZip.zip", outDirPath);
}

bool SSave::saveUncompressed(const QString &path, const QString &author)
{
    QFile file(path);

    if (file.open(QFile::WriteOnly | QFile::Text) == false) {
        reportError("Could not open file for saving: " + path);
        return false;
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

    // Write all pictures
    const QString outDirPath(QFileInfo(parsedPath).absolutePath());
    QDir pictureDir(QFileInfo(parsedPath).absoluteDir());
    if (!pictureDir.exists(Tags::picturesDir)) {
        pictureDir.mkdir(Tags::picturesDir);
    }
    pictureDir.cd(Tags::picturesDir);

    const QStringList existingPics(pictureDir.entryList(QDir::Files | QDir::NoDotAndDotDot));
    const QFileInfoList sourcePics(QDir(basePicturePath()).entryInfoList(QDir::Files | QDir::NoDotAndDotDot));
    for (auto pic: sourcePics) {
        if (!existingPics.contains(pic.fileName())) {
            QFile::copy(basePicturePath() + "/" + pic.fileName(),
                        pictureDir.absolutePath() + "/" + pic.fileName());
        }
    }
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
