#ifndef SEVENTPTR_H
#define SEVENTPTR_H

#include <QSharedPointer>
#include <QVector>

class SEvent;

using SEventPtr = QSharedPointer<SEvent>;
using SEventVector = QVector<SEventPtr>;

#endif // SEVENTPTR_H
