#include "splotsmodel.h"
#include "splot.h"

/*!
 * \class SPlotsModel
 * \brief MVC model holding all defined plots
 */

SPlotsModel::SPlotsModel(QObject *parent) : QObject(parent)
{

}

QByteArray SPlotsModel::insert(const QVector<QByteArray> &ids, const QString &name)
{
    auto plot = new SPlot;
    plot->setName(name);
    plot->setObjects(ids);
    return plot->id();
}
