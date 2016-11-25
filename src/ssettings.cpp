#include "ssettings.h"
#include "tags.h"

#include <QSettings>

SSettings::SSettings(QObject *parent) : QObject(parent)
{
    load();
}

SSettings::~SSettings()
{
    save();
}

void SSettings::load()
{
    QSettings settings;
    autoLoadLastFile = settings.value(Tags::autoLoadLastFile, true).toBool();
    autoSaveOnExit = settings.value(Tags::autoSaveOnExit, true).toBool();
    lastOpenFilePath = settings.value(Tags::lastOpenFilePath).toString();
    lastSaveFilePath = settings.value(Tags::lastSaveFilePath).toString();
    author = settings.value(Tags::author).toString();
}

void SSettings::save() const
{
    QSettings settings;
    settings.setValue(Tags::autoLoadLastFile, autoLoadLastFile);
    settings.setValue(Tags::autoSaveOnExit, autoSaveOnExit);
    settings.setValue(Tags::lastOpenFilePath, lastOpenFilePath);
    settings.setValue(Tags::lastSaveFilePath, lastSaveFilePath);
    settings.setValue(Tags::author, author);
}
