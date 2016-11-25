#ifndef SQMLASSISTANT_H
#define SQMLASSISTANT_H

#include <QObject>

class QQmlEngine;
class QJSEngine;

class SQmlAssistant : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int buttonMargin READ buttonMargin CONSTANT)

public:
    explicit SQmlAssistant(QObject *parent = 0);

    int buttonMargin() const;

    // First, define the singleton type provider function (callback).
    static QObject *assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
};

#endif // SQMLASSISTANT_H
