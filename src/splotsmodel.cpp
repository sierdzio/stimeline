#include "splotsmodel.h"

#include <QJsonArray>
#include <QJsonValue>

/*!
 * \class SPlotsModel
 * \brief MVC model holding all defined plots
 */

SPlotsModel::SPlotsModel(QObject *parent) : QObject(parent)
{

}

void SPlotsModel::clear()
{
    mPlots.clear();
}

QJsonArray SPlotsModel::toJson() const
{
    QJsonArray result;

    for (const auto &plot: qAsConst(mPlots)) {
        result.append(plot.toJson());
    }

    return result;
}

void SPlotsModel::fromJson(const QJsonArray &json)
{
    mPlots.clear();
    for (const QJsonValue &i: json) {
        const QJsonObject obj(i.toObject());

        SPlot plot;
        plot.fromJson(obj);
        mPlots.insert(plot.id(), plot);
    }
}

QString SPlotsModel::value(const QByteArray &key) const
{
    return mPlots.value(key).name();
}

QByteArray SPlotsModel::insert(const QVector<QByteArray> &ids, const QString &name)
{
    SPlot plot;
    plot.setName(name);
    plot.setObjects(ids);
    mPlots.insert(plot.id(), plot);
    return plot.id();
}
