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
    Q_PROPERTY(qreal viewScale READ viewScale WRITE setViewScale NOTIFY viewScaleChanged)

public:
    EventTimelineView(QQuickItem *parent = nullptr);

    Q_INVOKABLE void scrollLeft(const quint64 amount);
    Q_INVOKABLE void scrollRight(const quint64 amount);

    void setViewScale(const qreal value);
    qreal viewScale() const; //!< K

signals:
    void timelineChanged(STimeline *timeline) const;
    void viewScaleChanged(qreal scale) const;

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

    qreal verticalCenter() const;
    qreal horizontalCenter() const;

private:
    quint64 mWindowStart = 0;
    quint64 mWindowEnd = 0;
    quint64 mNow = 0;
    qreal mScale = 1.0;

    bool mScaleChanged = false;
    bool mNowChanged = false;

    QSGNode *mMainNode = nullptr;
    QSGGeometryNode *mScaleNode = nullptr;
    QSGGeometryNode *mNowMarkersNode = nullptr;
    STimeline * mTimeline = nullptr;
};
