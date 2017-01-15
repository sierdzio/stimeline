#include "sassistant.h"
#include "sobject.h"

#include <QDateTime>
#include <QCryptographicHash>

SAssistant::SAssistant(QObject *parent) : QObject(parent)
{

}

int SAssistant::buttonMargin() const
{
    return 25;
}

QString SAssistant::typeToString(const QString &type) const
{
    return SObject::typeToString(type);
}

QByteArray SAssistant::generateId()
{
    const QByteArray msecs(QByteArray::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()));
    const QByteArray result (QCryptographicHash::hash(msecs + QByteArray::number(qrand()) + "AA11",
                                                      QCryptographicHash::Sha1));
    return result.toHex();
}

QString SAssistant::cleanPath(const QString &urlPath)
{
    const QLatin1String fileUrl("file://");
    if (urlPath.startsWith(fileUrl)) {
        return urlPath.mid(fileUrl.size());
    }

    return urlPath;
}

QObject *SAssistant::assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    SAssistant *assistant = new SAssistant();
    return assistant;
}
