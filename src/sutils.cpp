#include "sutils.h"

#include <QDateTime>
#include <QCryptographicHash>

SUtils::SUtils()
{

}

QByteArray SUtils::generateId()
{
    const QByteArray msecs(QByteArray::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()));
    const QByteArray result (QCryptographicHash::hash(msecs + QByteArray::number(qrand()) + "AA11",
                                                      QCryptographicHash::Sha1));
    return result;
}
