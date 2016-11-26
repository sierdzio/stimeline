#ifndef EVENTTIMELINE_H
#define EVENTTIMELINE_H

#include <QQuickItem>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(etl)

class QPointF;
class QColor;
class QSGNode;
class QSGGeometryNode;
class STimeline;

class EventTimeline : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(STimeline *timeline MEMBER mTimeline NOTIFY timelineChanged)

public:
    EventTimeline(QQuickItem *parent = nullptr);

signals:
    void timelineChanged(STimeline *timeline) const;

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *upnd) override;

    // Timeline HUD
    void drawNowMarkers(QSGNode *node) const;
    void drawScale(QSGNode *node) const;

    // Primitives
    QSGGeometryNode *drawLine(const QPointF &begin,
                              const QPointF &end,
                              const float width,
                              const QColor &color) const;
    QSGGeometryNode *drawPoint(const float x, const float y,
                               const float radius,
                               const QColor &color) const;
    QSGGeometryNode *drawText(const QPointF &point,
                              const QString &text,
                              const uint pointSize) const;

    qreal verticalCentre() const;
    qreal horizontalCenter() const;

private:
    STimeline * mTimeline;
};

#endif // EVENTTIMELINE_H
