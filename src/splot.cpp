#include "splot.h"
#include "sassistant.h"
#include "tags.h"

#include <QJsonValue>
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
    mId = qHash(SAssistant::generateId());
}

QJsonObject SPlot::toJson() const
{
    QJsonObject result;

    result.insert(Tags::id, QJsonValue(qint64(mId)));
    result.insert(Tags::name, QJsonValue(mName));
    result.insert(Tags::description, QJsonValue(mDescription));

    QString joined;
    for (const auto &value : mPlot) {
        if (!joined.isEmpty())
            joined += Tags::tagSeparator;

        if (!value.isEmpty())
            joined += value;
    }

    result.insert(Tags::tags, QJsonValue(joined));

    return result;
}

void SPlot::fromJson(const QJsonObject &json)
{
    mId = 0;
    mPlot.clear();
    mName.clear();
    mDescription.clear();

    mId = uint(json.value(Tags::id).toInt(0));
    mName = json.value(Tags::name).toString();
    mDescription = json.value(Tags::description).toString();
    const QString joined(json.value(Tags::tags).toString());
    const QStringList separated(joined.split(Tags::tagSeparator));

    for (const auto &value : separated) {
        mPlot.append(value.toLatin1());
    }
}

bool SPlot::contains(const QByteArray &id) const
{
    return mPlot.contains(id);
}

void SPlot::addObject(const QByteArray &id)
{
    mPlot.append(id);
}
