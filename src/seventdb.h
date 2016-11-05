#ifndef SEVENTDB_H
#define SEVENTDB_H

#include <QJsonObject>

#include "seventptr.h"

class SEventDB
{
public:
    SEventDB();

    void clear();

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    SEventVector mEvents;
};

#endif // SEVENTDB_H
