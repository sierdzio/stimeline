#ifndef SPLOT_H
#define SPLOT_H

#include <QVector>
#include <QObject>
#include <QJsonObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(splot)

class SPlot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER mName NOTIFY nameChanged)
    Q_PROPERTY(QString description MEMBER mDescription NOTIFY descriptionChanged)

public:
    explicit SPlot(QObject *parent = nullptr);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QByteArray id() const;

    void setName(const QString &name);
    void setObjects(const QVector<QByteArray> &ids);

signals:
    void nameChanged(const QString &name) const;
    void descriptionChanged(const QString &description) const;

public slots:
    bool contains(const QByteArray &id) const;
    void addObject(const QByteArray &id);

private:
    QByteArray mId;
    QVector<QByteArray> mPlot;
    QString mName;
    QString mDescription;
};

#endif // SPLOT_H
