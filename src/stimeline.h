#pragma once

#include <QVector>
#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

#include "sobject.h"

class SCalendar;
class SSettings;
//class SObject;
class SObjectModel;
class SObjectSortProxyModel;
class STagsModel;
class SErasModel;
class SPlotsModel;

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
    Q_PROPERTY(STagsModel* tags MEMBER mTags CONSTANT)
    Q_PROPERTY(SErasModel* eras MEMBER mEras CONSTANT)
    Q_PROPERTY(SPlotsModel* plots MEMBER mPlots CONSTANT)

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

    void addTag(SObject object, const QByteArray &tag);
    void removeTag(SObject object, const QByteArray &id);

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
    STagsModel *mTags = nullptr;
    SErasModel *mEras = nullptr;
    SPlotsModel *mPlots = nullptr;
};
