#ifndef SEVENTDB_H
#define SEVENTDB_H

#include <QJsonArray>

#include "seventptr.h"

class SEventDB
{
public:
    SEventDB();

    void clear();

    SEventVector events() const;

    QJsonArray toJson() const;
    virtual void fromJson(const QJsonArray &json);

protected:
    SEventVector mEvents;
};

#endif // SEVENTDB_H
