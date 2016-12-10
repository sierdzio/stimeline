#include "eventtimelineview.h"
#include "../stimeline.h"

#include <math.h>
#include <QPointF>
#include <QColor>
#include <QSGNode>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

#include <QQuickTextureFactory>
#include <QWheelEvent>

#include <QDebug>
Q_LOGGING_CATEGORY(etl, "EventTimeline")

EventTimelineView::EventTimelineView(QQuickItem *parent) : QQuickItem(parent)
{
    setWidth(3000);
    setFlag(QQuickItem::ItemHasContents, true);
}

void EventTimelineView::scrollLeft(const quint64 amount)
{
    mWindowStart -= amount;
    mNow -= amount;
    mWindowEnd -= amount;
    mNowChanged = true;
    updatePaintNode(mMainNode, nullptr);
}

void EventTimelineView::scrollRight(const quint64 amount)
{
    mWindowStart += amount;
    mNow += amount;
    mWindowEnd += amount;
    mNowChanged = true;
    updatePaintNode(mMainNode, nullptr);
}

void EventTimelineView::setScale(const qreal newScale)
{
    mScale = newScale;
    emit scaleChanged(newScale);
}

qreal EventTimelineView::scale() const
{
    return mScale;
}

QSGNode *EventTimelineView::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *upnd)
{
    Q_UNUSED(upnd);

    QSGGeometryNode *nd = static_cast<QSGGeometryNode *>(node);
    if (!nd) {
        // Main vertical line
        nd = drawLine(QPointF(0, verticalCenter()),
                      QPointF(width(), verticalCenter()),
                      6, QColor(255, 0, 0));
        mScaleNode = drawScale();

        nd->appendChildNode(mScaleNode);

        mMainNode = nd;
    }

    if (mScaleChanged) {
        qDebug(etl) << "Updating scale" << scale();
        mScaleChanged = false;
        mNowChanged = true;
    }

    if (mNowChanged) {
        qDebug(etl) << "Updating timeline. New NOW position:" << mNow
                    << "left:" << mWindowStart << "right:" << mWindowEnd;
        mNowChanged = false;

        nd = drawLine(QPointF(0, verticalCenter()),
                      QPointF(width(), verticalCenter()),
                      6*scale(), QColor(255, 0, 0));
        mScaleNode = drawScale();

        nd->appendChildNode(mScaleNode);

        mMainNode = nd;
        nd->markDirty(QSGNode::DirtyGeometry);
    }

    return nd;
}

void EventTimelineView::wheelEvent(QWheelEvent *event)
{
    const int eventDelta(event->delta());
    if (eventDelta > 0) {
        setScale(scale() - 0.1);
        mScaleChanged = true;
        updatePaintNode(mMainNode, nullptr);
    } else if (eventDelta < 0) {
        setScale(scale() + 0.1);
        mScaleChanged = true;
        updatePaintNode(mMainNode, nullptr);
    }
}

/*!
 * Draws the short bars shown at the top and bottom of the Item. Bars are
 * added as subnodes to \a node.
 */
QSGGeometryNode *EventTimelineView::drawNowMarkers() const
{
    const qreal hCenter(horizontalCenter());
    QSGGeometryNode *top = drawLine(QPointF(hCenter, 0.0),
                                    QPointF(hCenter, 12.0),
                                    4.0,
                                    Qt::darkGray);
    QSGGeometryNode *bottom = drawLine(QPointF(hCenter, height()-12.0),
                                       QPointF(hCenter, height()),
                                       4.0,
                                       Qt::darkGray);

    top->appendChildNode(bottom);
    return top;
}

/*!
 * Draws small markers visualising the timespan visible in the timeline.
 * Adds text to markers to show the represented date.
 */
QSGGeometryNode *EventTimelineView::drawScale() const
{
    QSGGeometryNode *result = nullptr;
    // TODO: scale drawing logic ;-)
    const QColor barColor(Qt::gray);
    const float barWidth(4.0);
    const qreal y(verticalCenter());
    const qreal endY(verticalCenter() + 12.0);
    const uint barCount(scale()*8);
    const uint spacing(width() / barCount);

    for (uint i = 0; i < barCount; ++i) {
        const qreal x(i * spacing);

        QSGGeometryNode *bar = drawLine(QPointF(x, y), QPointF(x, endY),
                                        barWidth, barColor);
        if (result)
            result->appendChildNode(bar);
        else
            result = bar;
    }

    return result;
}

QSGGeometryNode *EventTimelineView::drawLine(const QPointF &begin, const QPointF &end,
                                         const float width,
                                         const QColor &color) const
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(GL_LINES);
    geometry->setLineWidth(width);
    geometry->vertexDataAsPoint2D()[0].set(begin.x(), begin.y());
    geometry->vertexDataAsPoint2D()[1].set(end.x(), end.y());

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);

    QSGGeometryNode *node = new QSGGeometryNode;
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}

QSGGeometryNode *EventTimelineView::drawPoint(const float x, const float y,
                                          const float radius,
                                          const QColor &color) const
{
    const uint pointCount = 18;
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                            pointCount);
    geometry->setDrawingMode(GL_TRIANGLE_FAN);
    geometry->setLineWidth(1);
    auto point2d = geometry->vertexDataAsPoint2D();

    point2d[0].set(x, y);
    for (uint i = 1; i < pointCount; ++i)
    {
        const float angle = float(i * 2 * M_PI / (pointCount - 2));
        point2d[i].set(x + (radius * cos(angle)),
                       y - (radius * sin(angle)));
    }

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);

    QSGGeometryNode *node = new QSGGeometryNode;
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}

QSGGeometryNode *EventTimelineView::drawText(const QPointF &point,
                                         const QString &text,
                                         const uint pointSize) const
{
    Q_UNUSED(point);
    Q_UNUSED(text);
    Q_UNUSED(pointSize);

    return nullptr;
}

qreal EventTimelineView::verticalCenter() const
{
    return height()/2;
}

qreal EventTimelineView::horizontalCenter() const
{
    return width()/2;
}
