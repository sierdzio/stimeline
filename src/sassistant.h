#pragma once

#include <QObject>

#include "sobject.h"
#include "sdatetime.h"

class QQmlEngine;
class QJSEngine;

class SAssistant : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int buttonMargin READ buttonMargin CONSTANT)
    Q_PROPERTY(int cardWidth READ cardWidth CONSTANT)
    Q_PROPERTY(QString extensionCompressed READ extensionCompressed CONSTANT)
    Q_PROPERTY(QString extensionUncompressed READ extensionUncompressed CONSTANT)

public:
    enum States {
        Hidden,
        Visible
    };
    Q_ENUM(States)

    explicit SAssistant(QObject *parent = 0);

    static int buttonMargin(); //!< K
    static int cardWidth(); //!< K
    static QString extensionCompressed(); //!< K
    static QString extensionUncompressed(); //!< K
    Q_INVOKABLE static QString typeToString(const QString &type);
    Q_INVOKABLE static QByteArray generateId();
    Q_INVOKABLE static QString directory(const QString &filePath);
    static QByteArray fileChecksum(const QString &filePath);
    static QString cleanPath(const QString &urlPath);

    Q_INVOKABLE SObject defaultObject() const;
    Q_INVOKABLE SDateTime defaultDateTime() const;
    Q_INVOKABLE SDateTime dateFromString(const QString &dateTime) const;

    // Define the singleton type provider function (callback).
    static QObject *assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    const SObject mDefaultObject;
    const SDateTime mDefaultDateTime;
};
