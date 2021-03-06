#pragma once

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(ssettings)

class SSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoLoadLastFile READ autoLoadLastFile WRITE setAutoLoadLastFile NOTIFY autoLoadLastFileChanged)
    Q_PROPERTY(bool autoSaveOnExit READ autoSaveOnExit WRITE setAutoSaveOnExit NOTIFY autoSaveOnExitChanged)
    Q_PROPERTY(bool useSimpleFileDialog READ useSimpleFileDialog WRITE setUseSimpleFileDialog NOTIFY useSimpleFileDialogChanged)
    Q_PROPERTY(QString configDir READ configDir WRITE setConfigDir NOTIFY configDirChanged)
    Q_PROPERTY(QString lastOpenFilePath READ lastOpenFilePath WRITE setLastOpenFilePath NOTIFY lastOpenFilePathChanged)
    Q_PROPERTY(QString lastOpenFileName READ lastOpenFileName WRITE setLastOpenFileName NOTIFY lastOpenFileNameChanged)
    Q_PROPERTY(QString lastOpenFileExtension READ lastOpenFileExtension WRITE setLastOpenFileExtension NOTIFY lastOpenFileExtensionChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit SSettings(QObject *parent = 0);
    ~SSettings();

    void load();
    void save() const;

    bool autoLoadLastFile() const;
    bool autoSaveOnExit() const;
    bool useSimpleFileDialog() const;
    QString configDir() const;
    QString lastOpenFilePath() const;
    QString lastOpenFileName() const;
    QString lastOpenFileExtension() const;
    QString author() const;    
    QString name() const;    

public slots:
    void setAutoLoadLastFile(bool autoLoadLastFile);
    void setAutoSaveOnExit(bool autoSaveOnExit);
    void setUseSimpleFileDialog(bool useSimpleFileDialog);
    void setConfigDir(const QString &configDir);
    void setLastOpenFilePath(const QString &lastOpenFilePath);
    void setLastOpenFileName(const QString &lastOpenFileName);
    void setLastOpenFileExtension(const QString &lastOpenFileExtension);
    void setAuthor(const QString &author);
    void setName(const QString &name);

signals:
    void autoSaveOnExitChanged(bool newValue) const; //!< K
    void autoLoadLastFileChanged(bool newValue) const; //!< K
    void useSimpleFileDialogChanged(bool newValue) const; //!< K
    void configDirChanged(QString configDir); //!< K
    void lastOpenFilePathChanged(const QString &newPath) const; //!< K
    void lastOpenFileNameChanged(const QString &mLastOpenFileName) const; //!< K
    void lastOpenFileExtensionChanged(const QString &mLastOpenFileExtension) const; //!< K
    void authorChanged(const QString &mAuthor) const; //!< K    
    void nameChanged(const QString &name); //!< K

protected slots:
    void updateLastOpenedFileData(const QString &lastOpenFile);

private:
    bool mAutoLoadLastFile = true;
    bool mAutoSaveOnExit = true;
    bool mUseSimpleFileDialog = false;
    QString mConfigDir;
    QString mLastOpenFilePath;
    QString mLastOpenFileName;
    QString mLastOpenFileExtension;
    QString mAuthor = "Testing Tom";
    QString mName;
};
