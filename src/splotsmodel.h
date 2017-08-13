#pragma once

#include <QVector>
#include <QObject>

class SPlot;

class SPlotsModel : public QObject
{
    Q_OBJECT
public:
    explicit SPlotsModel(QObject *parent = nullptr);

public slots:
    QByteArray insert(const QVector<QByteArray> &ids, const QString &name);

private:
    QVector<SPlot *> mPlots;
};
