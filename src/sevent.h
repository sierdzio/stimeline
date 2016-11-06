#ifndef SEVENT_H
#define SEVENT_H

#include "sdatetime.h"

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sevent)

class SEvent: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QByteArray id MEMBER mId)
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString description MEMBER mDescription)
    Q_PROPERTY(SDateTime from MEMBER mFrom)
    Q_PROPERTY(SDateTime to MEMBER mTo)

public:
    SEvent();
    SEvent(const QJsonObject &from);

    QByteArray id() const;
    bool isValid() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    QByteArray mId;
    QString mName;
    QString mDescription;
    SDateTime mFrom;
    SDateTime mTo;
};

//Q_DECLARE_METATYPE(SEvent)
Q_DECLARE_METATYPE(SEvent*)

#endif // SEVENT_H
