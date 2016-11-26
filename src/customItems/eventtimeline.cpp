#include "eventtimeline.h"
#include "../stimeline.h"

#include <math.h>
#include <QPointF>
#include <QColor>
#include <QSGNode>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

#include <QDebug>
Q_LOGGING_CATEGORY(etl, "EventTimeline")

EventTimeline::EventTimeline(QQuickItem *parent) : QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode *EventTimeline::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *upnd)
{
    Q_UNUSED(upnd);

    QSGGeometryNode *nd = static_cast<QSGGeometryNode *>(node);
    if (!nd) {
        // Main vertical line
        nd = drawLine(QPointF(0, verticalCentre()),
                      QPointF(width(), verticalCentre()),
                      6, QColor(255, 0, 0));
        drawScale(nd);

        // Now markers
        drawNowMarkers(nd);

        // Draw event marker
        // (temp)
        nd->appendChildNode(drawPoint(float(horizontalCenter()), float(verticalCentre()),
                                      12.0, Qt::blue));
    }

    return nd;
}

/*!
 * Draws the short bars shown at the top and bottom of the Item. Bars are
 * added as subnodes to \a node.
 */
void EventTimeline::drawNowMarkers(QSGNode *node) const
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

    node->appendChildNode(top);
    node->appendChildNode(bottom);
}

/*!
 * Draws small markers visualising the timespan visible in the timeline.
 * Adds text to markers to show the represented date.
 */
void EventTimeline::drawScale(QSGNode *node) const
{
    // TODO: scale drawing logic ;-)
    const QColor barColor(Qt::gray);
    const float barWidth(4.0);
    const qreal y(verticalCentre());
    const qreal endY(verticalCentre() + 12.0);
    const uint barCount(scale()*8);
    const uint spacing(width() / barCount);

    for (uint i = 0; i < barCount; ++i) {
        const qreal x(i * spacing);
        node->appendChildNode(drawLine(QPointF(x, y), QPointF(x, endY),
                                       barWidth, barColor));
    }
}

QSGGeometryNode *EventTimeline::drawLine(const QPointF &begin, const QPointF &end,
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

QSGGeometryNode *EventTimeline::drawPoint(const float x, const float y,
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

QSGGeometryNode *EventTimeline::drawText(const QPointF &point,
                                         const QString &text,
                                         const uint pointSize) const
{
    Q_UNUSED(point);
    Q_UNUSED(text);
    Q_UNUSED(pointSize);

    return nullptr;
}

qreal EventTimeline::verticalCentre() const
{
    return height()/2;
}

qreal EventTimeline::horizontalCenter() const
{
    return width()/2;
}
