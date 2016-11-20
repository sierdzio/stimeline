#ifndef STIMELINE_H
#define STIMELINE_H

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stimeline)

class SCalendar;
class SSettings;
class SEventModel;

class STimeline : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SEventModel* eventModel MEMBER mEventModel CONSTANT)
    Q_PROPERTY(SSettings* settings MEMBER mSettings CONSTANT)
    Q_PROPERTY(SCalendar* calendar MEMBER mCalendar CONSTANT)

public:
    STimeline(SSettings *settings = nullptr, QObject *parent = nullptr);
    ~STimeline();

public slots:
    void load(const QString &path);
    void save(const QString &path) const;

signals:
    void error(const QString &message) const;

private:
    void init();
    void reportError(const QString &message) const;
    QString cleanPath(const QString &urlPath) const;

    SSettings *mSettings = nullptr;
    SEventModel *mEventModel = nullptr;
    SCalendar *mCalendar = nullptr;

    // TODO: add:
    // People
    // Objects
    // Places
    // Maps
};

#endif // STIMELINE_H
