#ifndef SEVENTDB_H
#define SEVENTDB_H

#include <QJsonArray>

#include "seventptr.h"

class SEventDB
{
public:
    SEventDB();

    void clear();

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

private:
    SEventVector mEvents;
};

#endif // SEVENTDB_H
