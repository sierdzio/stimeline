#ifndef SUTILS_H
#define SUTILS_H

#include <QByteArray>

// TODO: make Singleton?
class SUtils
{
public:
    SUtils();

    static QByteArray generateId();
};

#endif // SUTILS_H
