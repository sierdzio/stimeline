#pragma once

#include <QVector>
#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

class SCalendar;
class SSettings;
class SObjectModel;
class SObjectSortProxyModel;
class SObjectTags;

class STimeline : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SObjectSortProxyModel* eventModelProxy MEMBER mEventModelProxy CONSTANT)
    Q_PROPERTY(SObjectModel* eventModel MEMBER mEventModel CONSTANT)
    Q_PROPERTY(SObjectModel* personModel MEMBER mPersonModel CONSTANT)
    Q_PROPERTY(SObjectModel* artifactModel MEMBER mArtifactModel CONSTANT)
    Q_PROPERTY(SObjectModel* placeModel MEMBER mPlaceModel CONSTANT)
    Q_PROPERTY(SObjectModel* mapModel MEMBER mMapModel CONSTANT)
    Q_PROPERTY(SSettings* settings MEMBER mSettings CONSTANT)
    Q_PROPERTY(SCalendar* calendar MEMBER mCalendar CONSTANT)
    Q_PROPERTY(SObjectTags* tags MEMBER mTags CONSTANT)
    // mTags

public:
    STimeline(SSettings *settings = nullptr, QObject *parent = nullptr);
    ~STimeline();

public slots:
    void clear();
    void load(const QString &path);
    void save(const QString &path) const;
    void exportSave() const;

    void loadCalendar(const QString &path);
    void saveCalendar(const QString &path) const;

    QString loadPicture(const QString &absolutePath);
    // TODO: make property
    QString basePicturePath() const;

    SObjectModel *model(const QString &type) const;
    SObjectModel *model(const int type) const;

private:
    void init();

    QString mRuntimeDataPath;
    QVector<QByteArray> mPictureCache;
    SSettings *mSettings = nullptr;
    SObjectSortProxyModel *mEventModelProxy = nullptr;
    SCalendar *mCalendar = nullptr;
    SObjectModel *mEventModel = nullptr;
    SObjectModel *mPersonModel = nullptr;
    SObjectModel *mArtifactModel = nullptr;
    SObjectModel *mPlaceModel = nullptr;
    SObjectModel *mMapModel = nullptr;
    SObjectTags *mTags = nullptr;
};
