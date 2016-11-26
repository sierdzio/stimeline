#include "eventtimeline.h"

#include <math.h>
#include <QColor>
#include <QSGNode>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

#include <QDebug>
Q_LOGGING_CATEGORY(etl, "EventTimeline")

EventTimeline::EventTimeline()
{
    setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode *EventTimeline::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *upnd)
{
    Q_UNUSED(upnd);

    QSGGeometryNode *nd = static_cast<QSGGeometryNode *>(node);
    if (!nd) {
        // Main vertical line
        nd = drawLine(0, float(verticalCentre()),
                      float(width()), float(verticalCentre()),
                      6, QColor(255, 0, 0));
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
    const float hCenter(horizontalCenter());
    QSGGeometryNode *top = drawLine(hCenter, 0.0,
                                    hCenter, 12.0, 4.0,
                                    Qt::darkGray);
    QSGGeometryNode *bottom = drawLine(hCenter, float(height()-12.0),
                                       hCenter, float(height()), 4.0,
                                       Qt::darkGray);

    node->appendChildNode(top);
    node->appendChildNode(bottom);
}

QSGGeometryNode *EventTimeline::drawLine(const float x, const float y,
                                         const float endX, const float endY, const float width,
                                         const QColor &color) const
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(GL_LINES);
    geometry->setLineWidth(width);
    geometry->vertexDataAsPoint2D()[0].set(x, y);
    geometry->vertexDataAsPoint2D()[1].set(endX, endY);

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

qreal EventTimeline::verticalCentre() const
{
    return height()/2;
}

qreal EventTimeline::horizontalCenter() const
{
    return width()/2;
}
