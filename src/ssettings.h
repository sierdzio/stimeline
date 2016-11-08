#ifndef SSETTINGS_H
#define SSETTINGS_H

#include <QString>
#include <QObject>

class SSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoLoadLastFile MEMBER autoLoadLastFile NOTIFY autoLoadLastFileChanged)
    Q_PROPERTY(QString lastOpenFilePath MEMBER lastOpenFilePath NOTIFY lastOpenFilePathChanged)
    Q_PROPERTY(QString lastSaveFilePath MEMBER lastSaveFilePath NOTIFY lastSaveFilePathChanged)

public:
    explicit SSettings(QObject *parent = 0);
    ~SSettings();

    void load();
    void save() const;

    bool autoLoadLastFile = true;
    QString lastOpenFilePath;
    QString lastSaveFilePath;

signals:
    void autoLoadLastFileChanged(bool newValue) const;
    void lastOpenFilePathChanged(const QString &newPath) const;
    void lastSaveFilePathChanged(const QString &newPath) const;
};

#endif // SSETTINGS_H
