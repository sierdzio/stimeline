#ifndef SPLOT_H
#define SPLOT_H

#include <QVector>
#include <QObject>
#include <QJsonArray>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(splot)

class SPlot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString description MEMBER mDescription)

public:
    explicit SPlot(QObject *parent = nullptr);

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

public slots:
    bool contains(const QByteArray &id) const;
    void addObject(const QByteArray &id);

private:
    QVector<QByteArray> mPlot;
    QString mName;
    QString mDescription;
};

#endif // SPLOT_H
