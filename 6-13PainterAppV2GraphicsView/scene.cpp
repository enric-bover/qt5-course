#include "scene.h"
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include "resizableellipseitem.h"
#include "resizablepixmapitem.h"
#include "resizablerectitem.h"
#include "resizablestaritem.h"
#include <QGraphicsSceneMouseEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    tool(Cursor),
    drawing(false)
{

}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
     if(event->mimeData()->property("Key").canConvert(QMetaType::Int)){
         event->acceptProposedAction();
     }else{
         QGraphicsScene::dragMoveEvent(event);
     }
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->property("Key").canConvert(QMetaType::Int)){

        int key = event->mimeData()->property("Key").toInt();


        switch (key) {
        case 10:{
            //Ellipse
            ResizableEllipseItem * ellipse = new ResizableEllipseItem();
            ellipse->setRect(0,0,80,50);
            ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            ellipse->setBrush(Qt::gray);
            addItem(ellipse);

            ellipse->setPos(event->scenePos() -QPointF((ellipse->boundingRect().width()/2),
                                                       (ellipse->boundingRect().height()/2))) ;

        }
            break;
        case 20:{
            //Qt Quick Image
            ResizablePixmapItem * pixItem = new ResizablePixmapItem(QPixmap(":/images/quick.png"));
            pixItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            addItem(pixItem);
            pixItem->setPos(event->scenePos() -QPointF((pixItem->boundingRect().width()/2),
                                                       (pixItem->boundingRect().height()/2))) ;
        }
            break;
        case 30:{
            //Rectangle
            ResizableRectItem * rectItem = new ResizableRectItem();
            rectItem->setRect(0,0,80,50);
            rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            rectItem->setBrush(Qt::gray);
            addItem(rectItem);
            rectItem->setPos(event->scenePos() -QPointF((rectItem->boundingRect().width()/2),
                                                       (rectItem->boundingRect().height()/2))) ;
        }
            break;
        case 40:{
            //Star
            ResizableStarItem * starItem = new ResizableStarItem();
            starItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            starItem->setBrush(Qt::gray);
            addItem(starItem);
            starItem->setPos(event->scenePos() -QPointF((starItem->boundingRect().width()/2),
                                                       (starItem->boundingRect().height()/2))) ;
        }
            break;

        }



        event->acceptProposedAction();
    }else{
        QGraphicsScene::dropEvent(event);
    }

}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(tool == ToolType::Pen){
            startingPoint = event->scenePos();
            drawing = true;
        }
    } else{
        QGraphicsScene::mousePressEvent(event);

    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && drawing){
        if(tool == ToolType::Pen){
            drawLineTo(event->scenePos());
        }
    } else{
        QGraphicsScene::mouseMoveEvent(event);
    }

}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && drawing){
        if(tool == ToolType::Pen){
            lineGroup = nullptr;
            drawing = false;
        }
    } else{
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void Scene::drawLineTo(const QPointF &endPoint)
{
    if(!lineGroup){
        lineGroup = new QGraphicsItemGroup();
        lineGroup->setFlags(QGraphicsItem::ItemIsMovable |
                            QGraphicsItem::ItemIsSelectable);
        addItem(lineGroup);
        lastPenPoint = startingPoint;
    }
    QGraphicsLineItem * localLine = new QGraphicsLineItem(QLineF(lastPenPoint,endPoint));

    QPen mPen;
    mPen.setWidth(3);
    mPen.setColor(Qt::green);
    localLine->setPen(mPen);

    lineGroup->addToGroup(localLine);
    lastPenPoint = endPoint;
}

Scene::ToolType Scene::getTool() const
{
    return tool;
}

void Scene::setTool(ToolType newTool)
{
    tool = newTool;
}
