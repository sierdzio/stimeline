#include "sassistant.h"
#include "sobject.h"
#include "tags.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>

/*!
 * \class SAssistant
 *
 * Utility class, provides a wide assortment of convenience methods. An instance
 * is used as QML singleton, but the class is also available from C++.
 */

/*!
 * \enum SAssistant::States
 *
 * Typo-preventing convenience replacement for States strings in QML.
 */

/*!
 * \property SAssistant::buttonMargin
 *
 * The distance between a button and it's surrounding items.
 */

/*!
 * Default constructor, taking in a QObject \a parent.
 */
SAssistant::SAssistant(QObject *parent) : QObject(parent)
{
}

/*!
 * Returns the default button margin: the distance between a button and it's
 * surrounding items.
 */
int SAssistant::buttonMargin()
{
    return 25;
}

/*!
 * Returns default width of object card.
 */
int SAssistant::cardWidth()
{
    return 500;
}

/*!
 * Returns the file extension for compressed save.
 */
QString SAssistant::extensionCompressed()
{
    return Tags::extensionCompressed;
}

/*!
 * Returns the file extension for uncompressed save.
 */
QString SAssistant::extensionUncompressed()
{
    return Tags::extensionUncompressed;
}

/*!
 * Converts numeric \a type (for example coming from QML) into a string representation
 * of SObject::ObjectType enum and returns it.
 */
QString SAssistant::typeToString(const QString &type)
{
    return SObject::typeToString(type);
}

/*!
 * Returns a random ID generated based on some random numbers, current date and
 * time and a short salt.
 *
 * IDs are SHA1 checksums.
 */
QByteArray SAssistant::generateId()
{
    const QByteArray msecs(QByteArray::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()));
    const QByteArray result(QCryptographicHash::hash(msecs + QByteArray::number(qrand()) + "AA11",
                                                     QCryptographicHash::Sha1));
    return result.toHex();
}

/*!
 * Returns a SHA1 checksum of all data found under \a filePath or empty array
 * on error.
 */
QByteArray SAssistant::fileChecksum(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Can't provide a checksum for" << filePath << "file cannot be opened.";
        return QByteArray();
    }

    return QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha1).toHex();
}

/*!
 * Returns the \a urlPath stripped from "file://" prefix.
 */
QString SAssistant::cleanPath(const QString &urlPath)
{
    const QLatin1String fileUrl("file://");
    if (urlPath.startsWith(fileUrl)) {
        return urlPath.mid(fileUrl.size());
    }

    return urlPath;
}

SObject SAssistant::defaultObject() const
{
    return mDefaultObject;
}

SDateTime SAssistant::defaultDateTime() const
{
    return mDefaultDateTime;
}

SDateTime SAssistant::dateFromString(const QString &dateTime) const
{
    return SDateTime::fromString(dateTime);
}

/*!
 * Returns directory leading to \a filePath.
 */
QString SAssistant::directory(const QString &filePath)
{
    return QFileInfo(filePath).absolutePath();
}

/*!
 * Returns an instance of SAssistant to be used by QML \a engine and \a scriptEngine.
 */
QObject *SAssistant::assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    SAssistant *assistant = new SAssistant();
    return assistant;
}
