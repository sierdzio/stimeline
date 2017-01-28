#pragma once

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QVector>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(ssave)

class QJsonObject;
class SObjectModel;

class SSave
{
public:
    explicit SSave(const QString &runtimeDataPath = QString::null);
    QString runtimeDataPath() const;

    bool load(const QString &path);
    bool save(const QString &path);

    QJsonObject json() const;
    void setJson(const QJsonObject &json);

    QVector<QByteArray> pictureCache() const;

private:
    void init();
    bool loadCompressed(const QString &path);
    bool loadUncompressed(const QString &path);
    bool loadJson(const QString &path);
    bool loadPictures(const QString &path);

    bool saveCompressed(const QString &path);
    bool saveUncompressed(const QString &path);
    bool saveJson(const QString &path);
    bool savePictures(const QString &path);

    QString generateRuntimePath() const;
    void reportError(const QString &message);

    bool mIsError = false;
    // TODO: basePath, tempLocation,
    // save/load paths... think it through. We need a simple and robust solution
    QString mSaveDataPath;
    QString mLoadDataPath;
    QString mRuntimeDataPath;
    QVector<QByteArray> mPictureCache;
    QJsonObject mJson;
};
