#ifndef SPERSON_H
#define SPERSON_H

#include <QByteArray>
#include <QString>
#include <QObject>
#include <QJsonObject>

class SPerson
{
    Q_GADGET

    Q_PROPERTY(QByteArray id MEMBER mId)
    Q_PROPERTY(QByteArray picturePath MEMBER mPicturePath)
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString description MEMBER mDescription)

    friend class SPersonModel;

public:
    SPerson();
    SPerson(const QJsonObject &from);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    QByteArray mId;
    QByteArray mPicturePath;
    QString mName;
    QString mDescription;
};

#endif // SPERSON_H
