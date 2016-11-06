#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>

class qmlController : public QObject
{
    Q_OBJECT
public:
    explicit qmlController(QObject *parent = 0);

signals:

public slots:
};

#endif // QMLCONTROLLER_H