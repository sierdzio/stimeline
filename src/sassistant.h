#pragma once

#include <QObject>

class QQmlEngine;
class QJSEngine;

class SAssistant : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int buttonMargin READ buttonMargin CONSTANT)

public:
    enum States {
        Hidden,
        Visible
    };
    Q_ENUM(States)

    explicit SAssistant(QObject *parent = 0);

    static int buttonMargin();
    Q_INVOKABLE static QString typeToString(const QString &type);
    Q_INVOKABLE static QByteArray generateId();
    static QByteArray fileChecksum(const QString &filePath);
    static QString cleanPath(const QString &urlPath);

    // Define the singleton type provider function (callback).
    static QObject *assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
};
