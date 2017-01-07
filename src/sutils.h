#pragma once

#include <QByteArray>
#include <QString>

// TODO: make Singleton?
class SUtils
{
public:
    SUtils();

    static QByteArray generateId();
};
