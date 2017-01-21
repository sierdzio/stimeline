#include "ssettings.h"
#include "tags.h"

#include <QSettings>

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
 * \property SSettings::lastOpenFilePath
 *
 * Path to most recently opened file.
 */

/*!
 * \property SSettings::lastSaveFilePath
 *
 * Path to most recently saved file.
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
    QSettings settings;
    autoLoadLastFile = settings.value(Tags::autoLoadLastFile, true).toBool();
    autoSaveOnExit = settings.value(Tags::autoSaveOnExit, true).toBool();
    lastOpenFilePath = settings.value(Tags::lastOpenFilePath).toString();
    lastSaveFilePath = settings.value(Tags::lastSaveFilePath).toString();
    author = settings.value(Tags::author).toString();
}

/*!
 * Saves the settings to a file at default location.
 */
void SSettings::save() const
{
    QSettings settings;
    settings.setValue(Tags::autoLoadLastFile, autoLoadLastFile);
    settings.setValue(Tags::autoSaveOnExit, autoSaveOnExit);
    settings.setValue(Tags::lastOpenFilePath, lastOpenFilePath);
    settings.setValue(Tags::lastSaveFilePath, lastSaveFilePath);
    settings.setValue(Tags::author, author);
}
