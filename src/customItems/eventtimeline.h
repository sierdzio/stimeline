#ifndef EVENTTIMELINE_H
#define EVENTTIMELINE_H

#include <QQuickItem>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(etl)

class QColor;
class QSGNode;
class QSGGeometryNode;

class EventTimeline : public QQuickItem
{
    Q_OBJECT

public:
    EventTimeline();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *upnd) override;

    void drawNowMarkers(QSGNode *node) const;
    QSGGeometryNode *drawLine(const float x, const float y,
                              const float endX, const float endY,
                              const float width,
                              const QColor &color) const;
    QSGGeometryNode *drawPoint(const float x, const float y,
                               const float radius,
                               const QColor &color) const;

    qreal verticalCentre() const;
    qreal horizontalCenter() const;
};

#endif // EVENTTIMELINE_H
