#pragma once

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QVector>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(ssave)

class SSave
{
public:
    explicit SSave();

    bool load(const QString &path);
    bool save(const QString &path, const QString &author);

    QJsonObject json() const;

private:
    void init();
    bool loadCompressed(const QString &path);
    bool loadUncompressed(const QString &path);
    bool loadJson(const QString &path);
    bool loadPictures(const QString &path);

    bool saveCompressed(const QString &path, const QString &author);
    bool saveUncompressed(const QString &path, const QString &author);

    void reportError(const QString &message);

    bool mIsError = false;
    // TODO: basePath, tempLocation,
    // save/load paths... think it through. We need a simple and robust solution
    QString mSavePath;
    QString mLoadPath;
    QVector<QByteArray> mPictureCache;
    QJsonObject mJson;
};
