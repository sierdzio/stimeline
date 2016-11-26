#include "eventtimeline.h"

#include <QSGNode>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGSimpleRectNode>
#include <QSGFlatColorMaterial>

EventTimeline::EventTimeline()
{
    setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode *EventTimeline::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *upnd)
{
    Q_UNUSED(upnd);

//    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node);
//    if (!n) {
//        n = new QSGSimpleRectNode();
//        n->setColor(Qt::red);
//    }
//    n->setRect(boundingRect());

    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(GL_LINES);
    geometry->setLineWidth(6);
    geometry->vertexDataAsPoint2D()[0].set(0, 0);
    geometry->vertexDataAsPoint2D()[1].set(width(), height());

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 0, 0));

    QSGGeometryNode *nd = new QSGGeometryNode;
    //QSGGeometryNode *nd = static_cast<QSGGeometryNode *>(node);
    nd->setGeometry(geometry);
    nd->setFlag(QSGNode::OwnsGeometry);
    nd->setMaterial(material);
    nd->setFlag(QSGNode::OwnsMaterial);

    return nd;
}
