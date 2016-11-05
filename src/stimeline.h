#ifndef STIMELINE_H
#define STIMELINE_H

#include <QString>
#include <QSharedPointer>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

class SCalendar;
class SEventDB;

class STimeline : public QObject
{
    Q_OBJECT

public:
    STimeline(QObject *parent = nullptr);

    void load(const QString &path);
    void save(const QString &path) const;

signals:
    void error(const QString &message) const;

private:
    void init();
    void reportError(const QString &message) const;

    QSharedPointer<SCalendar> mCalendar;
    QSharedPointer<SEventDB> mEventDB;
    // TODO: add:
    // People
    // Objects
    // Places
    // Maps
};

#endif // STIMELINE_H
