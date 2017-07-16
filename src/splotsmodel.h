#ifndef SPLOTSMODEL_H
#define SPLOTSMODEL_H

#include <QObject>

class SPlotsModel : public QObject
{
    Q_OBJECT
public:
    explicit SPlotsModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SPLOTSMODEL_H