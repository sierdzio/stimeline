#ifndef SEVENT_H
#define SEVENT_H

#include "seventptr.h"
#include "sdatetime.h"

#include <QVector>
#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sevent)

class SEvent
{
    Q_GADGET

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
    bool isRoot() const;

    SEventPtr parent() const;
    SEventVector children() const;

    QByteArray parentId() const;
    QVector<QByteArray> childrenIds() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QString toString() const;

private:
    QByteArray mId;
    QString mName;
    QString mDescription;
    SDateTime mFrom;
    SDateTime mTo;

    QByteArray mParentId;
    QVector<QByteArray> mChildrenIds;

    SEventPtr mParent;
    SEventVector mChildren;
};

#endif // SEVENT_H
