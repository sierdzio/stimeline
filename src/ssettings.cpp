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
    lastOpenFilePath = settings.value(Tags::lastOpenFilePath).toString();
}

void SSettings::save() const
{
    QSettings settings;
    settings.setValue(Tags::autoLoadLastFile, autoLoadLastFile);
    settings.setValue(Tags::lastOpenFilePath, lastOpenFilePath);
}
