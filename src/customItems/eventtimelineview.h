#pragma once

#include <QQuickItem>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(etl)

class QPointF;
class QColor;
class QSGNode;
class QSGGeometryNode;
class STimeline;

class EventTimelineView : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(STimeline *timeline MEMBER mTimeline NOTIFY timelineChanged)

public:
    EventTimelineView(QQuickItem *parent = nullptr);

signals:
    void timelineChanged(STimeline *timeline) const;

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *upnd) override;
    //virtual void mousePressEvent(QMouseEvent *event) override;
    //virtual void mouseMoveEvent(QMouseEvent *event) override;
    //virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    // Timeline HUD
    QSGGeometryNode *drawNowMarkers() const;
    QSGGeometryNode *drawScale() const;

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
    QSGNode *mMainNode = nullptr;
    QSGGeometryNode *mScaleNode = nullptr;
    QSGGeometryNode *mNowMarkersNode = nullptr;
    STimeline * mTimeline = nullptr;
    bool mScaleChanged = false;
};
