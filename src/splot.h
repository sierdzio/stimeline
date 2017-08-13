#pragma once

#include <QVector>
#include <QObject>
#include <QJsonObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(splot)

class SPlot
{
    Q_GADGET
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString description MEMBER mDescription)

public:
    explicit SPlot();

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QByteArray id() const;

    QString name() const;
    void setName(const QString &name);
    void setObjects(const QVector<QByteArray> &ids);

public slots:
    bool contains(const QByteArray &id) const;
    void addObject(const QByteArray &id);

private:
    QByteArray mId;
    QVector<QByteArray> mPlot;
    QString mName;
    QString mDescription;
};
