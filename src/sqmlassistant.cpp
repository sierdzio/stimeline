#include "sqmlassistant.h"

SQmlAssistant::SQmlAssistant(QObject *parent) : QObject(parent)
{

}

int SQmlAssistant::buttonMargin() const
{
    return 25;
}

QObject *SQmlAssistant::assistantSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    SQmlAssistant *assistant = new SQmlAssistant();
    return assistant;
}
