#include "splot.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

Q_LOGGING_CATEGORY(splot, "SPlot")

/*!
 * \class SPlot
 * \brief Used to define stories and plots within the general timeline.
 *
 * While the main timeline remains strictly chronological, a plot can contain
 * SObjects in any order.
 *
 * This is useful when writing a book/ story where the events are not unfolding
 * chronologically (for example, retrospective is used). Multiple SPlots can
 * point to the same SObject/ event, or unfold in parallel, thus enabling the
 * author to represent telling multiple stories simultaneously.
 */

SPlot::SPlot(QObject *parent) : QObject(parent)
{
}

QJsonArray SPlot::toJson() const
{
    QJsonArray result;

//    for (auto it = mTags.constBegin(); it != mTags.constEnd(); ++it) {
//        result.append(QJsonValue(QJsonObject({{QString::number(it.key()),
//                                               it.value().value}})));
//    }

    return result;
}

void SPlot::fromJson(const QJsonArray &json)
{
    mPlot.clear();
    mName.clear();
    mDescription.clear();

//    for (const QJsonValue &i: json) {
//        const QJsonObject obj(i.toObject());
//        const QString keyString(obj.keys().first());
//        bool ok = false;

//        if (keyString.isEmpty()) {
//            qCDebug(splot) << "Empty tag key. This is normal if no tags are set.";
//            return;
//        }

//        const uint key(keyString.toUInt(&ok));

//        if (!ok) {
//            qCDebug(splot) << "ERROR: could not read Tag key" << obj;
//            return;
//        }

//        const QString value(obj.value(obj.keys().first()).toString());
//    }
}

bool SPlot::contains(const QByteArray &id) const
{
    return mPlot.contains(id);
}

void SPlot::addObject(const QByteArray &id)
{
    mPlot.append(id);
}
