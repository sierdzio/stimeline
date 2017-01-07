#pragma once

#include <QObject>

class QQmlEngine;
class QJSEngine;

class SQmlAssistant : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int buttonMargin READ buttonMargin CONSTANT)

public:
    enum States {
        Hidden,
        Visible
    };
    Q_ENUM(States)

    explicit SQmlAssistant(QObject *parent = 0);

    int buttonMargin() const;
    Q_INVOKABLE QString typeToString(const QString &type) const;

    // Define the singleton type provider function (callback).
    static QObject *assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
};
