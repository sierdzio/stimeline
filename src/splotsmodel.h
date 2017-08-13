#pragma once

#include "splot.h"

#include <QVector>
#include <QObject>

class SPlotsModel : public QObject
{
    Q_OBJECT
public:
    explicit SPlotsModel(QObject *parent = nullptr);
    void clear();

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

public slots:
    QString value(const QByteArray &key) const;
    QByteArray insert(const QVector<QByteArray> &ids, const QString &name);

private:
    QHash<QByteArray, SPlot> mPlots;
};
