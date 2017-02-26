#include "ssettings.h"
#include "tags.h"

#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>

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
SSettings::SSettings(QObject *parent) : QObject(parent)
{
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
    const QString defaultDataPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QSettings settings;
    autoLoadLastFile = settings.value(Tags::autoLoadLastFile, true).toBool();
    autoSaveOnExit = settings.value(Tags::autoSaveOnExit, true).toBool();
    useSimpleFileDialog = settings.value(Tags::useSimpleFileDialog, true).toBool();
    lastOpenFilePath = settings.value(Tags::lastOpenFilePath,
                                      defaultDataPath).toString();
    author = settings.value(Tags::author).toString();

    // Automatically populate last open file name and extension
    updateLastOpenedFileData(lastOpenFilePath);
}

/*!
 * Saves the settings to a file at default location.
 */
void SSettings::save() const
{
    QSettings settings;
    settings.setValue(Tags::autoLoadLastFile, autoLoadLastFile);
    settings.setValue(Tags::autoSaveOnExit, autoSaveOnExit);
    settings.setValue(Tags::useSimpleFileDialog, useSimpleFileDialog);
    settings.setValue(Tags::lastOpenFilePath, lastOpenFilePath);
    settings.setValue(Tags::author, author);
}

/*!
 * Updates lastOpenFileName and lastOpenFileExtension based on file path passed
 * in \a lastOpenFile.
 */
void SSettings::updateLastOpenedFileData(const QString &lastOpenFile)
{
    const QFileInfo fi(lastOpenFile);
    lastOpenFileName = fi.baseName();
    emit lastOpenFileNameChanged(lastOpenFileName);
    lastOpenFileExtension = fi.suffix();
    emit lastOpenFileExtensionChanged(lastOpenFileExtension);
}
