#include "ssettings.h"
#include "tags.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>

#include <QDebug>
Q_LOGGING_CATEGORY(ssettings, "SSettings")

/*!
 * \class SSettings
 *
 * Main settings handler. Used to save and load application settings to a file,
 * and to read option values at runtime.
 *
 * For it to work correctly, QApplication values need to be set (like application
 * name, version, organisation name and so on. See QSettings documentation).
 */

/*!
 * \property SSettings::autoLoadLastFile
 *
 * If true, last opened file will be automatically loaded on application startup.
 */

/*!
 * \property SSettings::autoSaveOnExit
 *
 * If true, the current timeline will be saved on exit.
 */

/*!
 * \property SSettings::useSimpleFileDialog
 *
 * If true, simple file dialog is used (on by default on Android). Otherwise,
 * a full blown file dialog is used.
 */

/*!
 * \property SSettings::configDir
 *
 * Path where config files are stored, as well as default calendars.
 */

/*!
 * \property SSettings::lastOpenFilePath
 *
 * Path to most recently opened file.
 */

/*!
 * \property SSettings::lastOpenFileName
 *
 * Name of the last opened file. Does not include extension.
 */

/*!
 * \property SSettings::lastOpenFileExtension
 *
 * Extension of the last opened file.
 */

/*!
 * \property SSettings::author
 *
 * Timeline author. This information is being saved in timeline file.
 */

/*!
 * Uses \a parent to join QObject hierarchy. Loads the settings.
 */
SSettings::SSettings(QObject *parent)
    : QObject(parent)
{
#ifdef Q_OS_ANDROID
    mConfigDir = (QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)//AppDataLocation)
#else
    mConfigDir = (QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
#endif
                 + "/" + Tags::docFolderName);

    load();

    // Automatically update lastOpenFileName and Extension
    connect(this, &SSettings::lastOpenFilePathChanged,
            this, &SSettings::updateLastOpenedFileData);
}

/*!
 * The destructor automatically saves current settings state to file.
 */
SSettings::~SSettings()
{
    save();
}

/*!
 * Loads the settings from default location.
 */
void SSettings::load()
{
    const QDir data(mConfigDir);

    if (!data.exists()) {
        qDebug(ssettings) << "Documents dir not present. Creating...";
        if (data.mkpath(mConfigDir)) {
            // Copy default calendars:
            const QString qrcPath(":/defaults/calendar/");
            for (const QString &fileName : QDir(qrcPath).entryList(QDir::Files)) {
                const QString filePath(qrcPath + fileName);
                qDebug(ssettings) << "Copying file:" << filePath
                         << data.absolutePath() + "/" + fileName
                         << "Result:" <<
                            QFile::copy(filePath,
                                        data.absolutePath() + "/" + fileName);
            }
            qDebug(ssettings) << "Done. Documents dir created and populated.";
        } else {
            qDebug(ssettings) << "Oh no! Could not create the documents dir!";
        }
    }

    QSettings settings(mConfigDir + "/" + Tags::settingsFileName,
                       QSettings::IniFormat);
    mAutoLoadLastFile = settings.value(Tags::autoLoadLastFile, true).toBool();
    mAutoSaveOnExit = settings.value(Tags::autoSaveOnExit, false).toBool();
    mUseSimpleFileDialog = settings.value(Tags::useSimpleFileDialog, true).toBool();
    mLastOpenFilePath = settings.value(Tags::lastOpenFilePath,
                                      QString(mConfigDir + "/timeline.json"))
            .toString();
    mAuthor = settings.value(Tags::author).toString();

    // Automatically populate last open file name and extension
    updateLastOpenedFileData(mLastOpenFilePath);
}

/*!
 * Saves the settings to a file at default location.
 */
void SSettings::save() const
{
    QSettings settings(mConfigDir + "/" + Tags::settingsFileName,
                       QSettings::IniFormat);
    settings.setValue(Tags::autoLoadLastFile, mAutoLoadLastFile);
    settings.setValue(Tags::autoSaveOnExit, mAutoSaveOnExit);
    settings.setValue(Tags::useSimpleFileDialog, mUseSimpleFileDialog);
    settings.setValue(Tags::lastOpenFilePath, mLastOpenFilePath);
    settings.setValue(Tags::author, mAuthor);
}

bool SSettings::autoLoadLastFile() const
{
    return mAutoLoadLastFile;
}

bool SSettings::autoSaveOnExit() const
{
    return mAutoSaveOnExit;
}

bool SSettings::useSimpleFileDialog() const
{
    return mUseSimpleFileDialog;
}

QString SSettings::configDir() const
{
    return mConfigDir;
}

QString SSettings::lastOpenFilePath() const
{
    return mLastOpenFilePath;
}

QString SSettings::lastOpenFileName() const
{
    return mLastOpenFileName;
}

QString SSettings::lastOpenFileExtension() const
{
    return mLastOpenFileExtension;
}

QString SSettings::author() const
{
    return mAuthor;
}

QString SSettings::name() const
{
    return mName;
}


void SSettings::setAutoLoadLastFile(bool autoLoadLastFile)
{
    if (mAutoLoadLastFile == autoLoadLastFile)
        return;

    mAutoLoadLastFile = autoLoadLastFile;
    emit autoLoadLastFileChanged(autoLoadLastFile);
}

void SSettings::setAutoSaveOnExit(bool autoSaveOnExit)
{
    if (mAutoSaveOnExit == autoSaveOnExit)
        return;

    mAutoSaveOnExit = autoSaveOnExit;
    emit autoSaveOnExitChanged(autoSaveOnExit);
}

void SSettings::setUseSimpleFileDialog(bool useSimpleFileDialog)
{
    if (mUseSimpleFileDialog == useSimpleFileDialog)
        return;

    mUseSimpleFileDialog = useSimpleFileDialog;
    emit useSimpleFileDialogChanged(useSimpleFileDialog);
}

void SSettings::setConfigDir(const QString &configDir)
{
    if (mConfigDir == configDir)
        return;

    mConfigDir = configDir;
    emit configDirChanged(mConfigDir);
}

void SSettings::setLastOpenFilePath(const QString &lastOpenFilePath)
{
    if (mLastOpenFilePath == lastOpenFilePath)
        return;

    mLastOpenFilePath = lastOpenFilePath;
    emit lastOpenFilePathChanged(lastOpenFilePath);
}

void SSettings::setLastOpenFileName(const QString &lastOpenFileName)
{
    if (mLastOpenFileName == lastOpenFileName)
        return;

    mLastOpenFileName = lastOpenFileName;
    emit lastOpenFileNameChanged(lastOpenFileName);
}

void SSettings::setLastOpenFileExtension(const QString &lastOpenFileExtension)
{
    if (mLastOpenFileExtension == lastOpenFileExtension)
        return;

    mLastOpenFileExtension = lastOpenFileExtension;
    emit lastOpenFileExtensionChanged(lastOpenFileExtension);
}

void SSettings::setAuthor(const QString &author)
{
    if (mAuthor == author)
        return;

    mAuthor = author;
    emit authorChanged(author);
}

void SSettings::setName(const QString &name)
{
    if (mName == name)
        return;

    mName = name;
    emit nameChanged(name);
}

/*!
 * Updates lastOpenFileName and lastOpenFileExtension based on file path passed
 * in \a lastOpenFile.
 */
void SSettings::updateLastOpenedFileData(const QString &lastOpenFile)
{
    const QFileInfo fi(lastOpenFile);
    mLastOpenFileName = fi.baseName();
    emit lastOpenFileNameChanged(mLastOpenFileName);
    mLastOpenFileExtension = fi.suffix();
    emit lastOpenFileExtensionChanged(mLastOpenFileExtension);
}
