#pragma once

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(ssettings)

class SSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoLoadLastFile MEMBER autoLoadLastFile NOTIFY autoLoadLastFileChanged)
    Q_PROPERTY(bool autoSaveOnExit MEMBER autoSaveOnExit NOTIFY autoSaveOnExitChanged)
    Q_PROPERTY(bool useSimpleFileDialog MEMBER useSimpleFileDialog NOTIFY useSimpleFileDialogChanged)
    Q_PROPERTY(QString lastOpenFilePath MEMBER lastOpenFilePath NOTIFY lastOpenFilePathChanged)
    Q_PROPERTY(QString lastOpenFileName MEMBER lastOpenFileName NOTIFY lastOpenFileNameChanged)
    Q_PROPERTY(QString lastOpenFileExtension MEMBER lastOpenFileExtension NOTIFY lastOpenFileExtensionChanged)
    Q_PROPERTY(QString author MEMBER author NOTIFY authorChanged)



public:
    explicit SSettings(QObject *parent = 0);
    ~SSettings();

    void load();
    void save() const;

    bool autoLoadLastFile = true;
    bool autoSaveOnExit = true;
    bool useSimpleFileDialog = false;
    QString lastOpenFilePath;
    QString lastOpenFileName;
    QString lastOpenFileExtension;
    QString author = "Testing Tom";
    QString defaultSettingsPath;

signals:
    void autoSaveOnExitChanged(bool newValue) const; //!< K
    void autoLoadLastFileChanged(bool newValue) const; //!< K
    void useSimpleFileDialogChanged(bool newValue) const; //!< K
    void lastOpenFilePathChanged(const QString &newPath) const; //!< K
    void lastOpenFileNameChanged(const QString &lastOpenFileName) const; //!< K
    void lastOpenFileExtensionChanged(const QString &lastOpenFileExtension) const; //!< K
    void authorChanged(const QString &author) const; //!< K

protected slots:
    void updateLastOpenedFileData(const QString &lastOpenFile);
};
