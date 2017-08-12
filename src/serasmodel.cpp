#include "serasmodel.h"
#include "sobjectmodel.h"
#include "sassistant.h"
#include "tags.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

Q_LOGGING_CATEGORY(serasmodel, "SErasModel")

/*!
 * \class SEra
 * \brief Eras, sometimes called "chapters", divide the timeline into unique
 * sections.
 *
 * Eras are used to separate different (chronological) set of events.
 */

SErasModel::SErasModel(QObject *parent) : QObject(parent)
{
}

void SErasModel::clear()
{
    mEras.clear();
}

QJsonArray SErasModel::toJson() const
{
    QJsonArray result;

    for (const auto &era: qAsConst(mEras)) {
        const QJsonObject obj({
                                  {Tags::id, QJsonValue(QString(era.id))},
                                  {Tags::name, QJsonValue(era.name)},
                                  {Tags::from, QJsonValue(QString(era.from))},
                                  {Tags::to, QJsonValue(QString(era.to))}
                              });

        result.append(obj);
    }

    return result;
}

void SErasModel::fromJson(const QJsonArray &json)
{
    mEras.clear();
    for (const QJsonValue &i: json) {
        const QJsonObject obj(i.toObject());

        SEra era;
        era.id = obj.value(Tags::id).toString().toLatin1();
        era.name = obj.value(Tags::name).toString();
        era.from = obj.value(Tags::from).toString().toLatin1();
        era.to = obj.value(Tags::to).toString().toLatin1();
        mEras.insert(era.id, era);
    }
}

/*!
 * Applies SEra defined by \a id to all relevant SObjects from \a model.
 *
 * In practice it means that all SObjects which start between SEra.from and
 * SEra.to, will save the SEra \a id internally.
 *
 * That info is used to display sections in event views.
 */
void SErasModel::applyTo(const QByteArray &id, SObjectModel *model)
{
    if (!model) {
        qDebug(serasmodel) << "Model is not valid:" << model;
        return;
    }

    if (!mEras.contains(id)) {
        qDebug(serasmodel) << "SEra with id" << id << "has not been found";
        return;
    }

    const SEra era = mEras.value(id);
    model->setEra(era.id, era.from, era.to);
}

/*!
 * Returns the name of given \a eraId. If the ID is not valid, this method will
 * return an empty string.
 */
QString SErasModel::name(const QByteArray &id) const
{
    return mEras.value(id).name;
}

QByteArray SErasModel::insert(const QString &name, const QByteArray &from, const QByteArray &to)
{
    const QByteArray id(SAssistant::generateId());

    //if (mEras.contains(id))
    //    ??;

    SEra era;
    era.id = id;
    era.name = name;
    era.from = from;
    era.to = to;

    mEras.insert(id, era);
    return id;
}

void SErasModel::remove(const QByteArray &id)
{
    mEras.remove(id);
}
