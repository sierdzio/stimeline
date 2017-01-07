#pragma once

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

class SCalendar;
class SSettings;
class SObjectModel;
class SEventSortProxyModel;

class STimeline : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SEventSortProxyModel* eventModelProxy MEMBER mEventModelProxy CONSTANT)
    Q_PROPERTY(SObjectModel* eventModel MEMBER mEventModel CONSTANT)
    Q_PROPERTY(SObjectModel* personModel MEMBER mPersonModel CONSTANT)
    Q_PROPERTY(SObjectModel* objectModel MEMBER mObjectModel CONSTANT)
    Q_PROPERTY(SObjectModel* placeModel MEMBER mPlaceModel CONSTANT)
    Q_PROPERTY(SObjectModel* mapModel MEMBER mMapModel CONSTANT)
    Q_PROPERTY(SSettings* settings MEMBER mSettings CONSTANT)
    Q_PROPERTY(SCalendar* calendar MEMBER mCalendar CONSTANT)

public:
    STimeline(SSettings *settings = nullptr, QObject *parent = nullptr);
    ~STimeline();

public slots:
    void load(const QString &path);
    void save(const QString &path) const;

    SObjectModel *model(const QString &type) const;
    SObjectModel *model(const int type) const;

signals:
    void error(const QString &message) const;

private:
    void init();
    void reportError(const QString &message) const;
    QString cleanPath(const QString &urlPath) const;

    SSettings *mSettings = nullptr;
    SEventSortProxyModel *mEventModelProxy = nullptr;
    SCalendar *mCalendar = nullptr;
    SObjectModel *mEventModel = nullptr;
    SObjectModel *mPersonModel = nullptr;
    SObjectModel *mObjectModel = nullptr;
    SObjectModel *mPlaceModel = nullptr;
    SObjectModel *mMapModel = nullptr;
};
