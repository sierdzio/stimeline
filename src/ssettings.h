#ifndef SSETTINGS_H
#define SSETTINGS_H

#include <QString>
#include <QObject>

class SSettings : public QObject
{
    Q_OBJECT

public:
    explicit SSettings(QObject *parent = 0);
    ~SSettings();

    void load();
    void save() const;

    bool autoLoadLastFile = true;
    QString lastOpenFilePath;
};

#endif // SSETTINGS_H
