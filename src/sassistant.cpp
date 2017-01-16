#include "sassistant.h"
#include "sobject.h"

#include <QFile>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>

SAssistant::SAssistant(QObject *parent) : QObject(parent)
{

}

int SAssistant::buttonMargin()
{
    return 25;
}

QString SAssistant::typeToString(const QString &type)
{
    return SObject::typeToString(type);
}

QByteArray SAssistant::generateId()
{
    const QByteArray msecs(QByteArray::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()));
    const QByteArray result(QCryptographicHash::hash(msecs + QByteArray::number(qrand()) + "AA11",
                                                      QCryptographicHash::Sha1));
    return result.toHex();
}

QByteArray SAssistant::fileChecksum(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Can't provide a checksum for" << filePath << "file cannot be opened.";
        return QByteArray();
    }

    return QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha1).toHex();
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
