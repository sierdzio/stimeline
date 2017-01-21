#ifndef SSAVER_H
#define SSAVER_H

#include <QObject>

class SSaver : public QObject
{
    Q_OBJECT
public:
    explicit SSaver(QObject *parent = 0);
    //SSaver(const QString &path);

    //void setPath(const QString &path);

    void load(const QString &path);
    void save(const QString &path) const;

//private:
    //QString mSavePath;
};

#endif // SSAVER_H
