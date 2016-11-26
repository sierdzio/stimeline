#ifndef EVENTTIMELINE_H
#define EVENTTIMELINE_H

#include <QQuickItem>

class QSGNode;

class EventTimeline : public QQuickItem
{
    Q_OBJECT

public:
    EventTimeline();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *upnd) override;
};

#endif // EVENTTIMELINE_H
