#include "resizablerectitem.h"
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

ResizableRectItem::ResizableRectItem()
{
    setOwnerItem(this);
    setAcceptDrops(true);
}

QRectF ResizableRectItem::boundingRect() const
{
    return selectorFrameBounds();
}

void ResizableRectItem::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect());
    drawHandlesIfNecessary();
}

QRectF ResizableRectItem::selectorFrameBounds() const
{
    return rect();
}

void ResizableRectItem::setSelectorFrameBounds(QRectF boundsRect)
{
    prepareGeometryChange();
    setRect(boundsRect);
    update();
}

void ResizableRectItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasColor()){
        event->acceptProposedAction();
    }else{
        QGraphicsRectItem::dragEnterEvent(event);
    }
}

void ResizableRectItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
     if(event->mimeData()->hasColor()){
         setBrush(QBrush(event->mimeData()->colorData().value <QColor>())) ;
          event->acceptProposedAction();
      }else{
          QGraphicsRectItem::dropEvent(event);
      }
}

QDataStream &operator<<(QDataStream &out, const ResizableRectItem & mRect){

      qreal x = mRect.selectorFrameBounds().x();
      qreal y = mRect.selectorFrameBounds().x();

      qreal width = mRect.selectorFrameBounds().width();
      qreal height = mRect.selectorFrameBounds().height();

      qreal posX = mRect.scenePos().x();
      qreal posY = mRect.scenePos().y();

      QColor brushColor = mRect.brush().color();
      QPen mPen = mRect.pen();

      out << x << y << width << height << posX << posY << brushColor.red()
          << brushColor.green() << brushColor.blue() <<
          mPen.color().red() << mPen.color().green() << mPen.color().blue() <<
          static_cast<int>(mPen.style()) << mPen.width();

      return out;


}

QDataStream &operator>>(QDataStream &in, ResizableRectItem & mRectItem){

}




