#ifndef STIMELINE_H
#define STIMELINE_H

#include "sevent.h"

#include <QString>
#include <QSharedPointer>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

class SCalendar;
class SEventDB;
class SSettings;
class SEventModel;

class STimeline : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QByteArray id MEMBER mId)
    Q_PROPERTY(SEventModel* eventModel MEMBER mEventModel CONSTANT)

public:
    STimeline(SSettings *settings = nullptr, QObject *parent = nullptr);

public slots:
    void load(const QString &path);
    void save(const QString &path) const;

signals:
    void error(const QString &message) const;

private:
    void init();
    void reportError(const QString &message) const;

    SSettings *mSettings = nullptr;
    SEventModel *mEventModel;

    QSharedPointer<SCalendar> mCalendar;
    QSharedPointer<SEventDB> mEventDB;
    // TODO: add:
    // People
    // Objects
    // Places
    // Maps
};

#endif // STIMELINE_H
