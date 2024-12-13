#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include "birditem.h"
#include <QGraphicsScene>

PillarItem::PillarItem() : topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2, 60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);


    int xRandomizer = QRandomGenerator::global()->bounded(200);

    yPos = QRandomGenerator::global()->bounded(150);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));


    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    QObject::connect(xAnimation,&QPropertyAnimation::finished,[=](){
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting pillar";

    delete topPillar;
    delete bottomPillar;


}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal newX)
{

    m_x = newX;
    setPos(QPointF(0,0) + QPointF(m_x, yPos));
}

bool PillarItem::CollidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem * item, collidingItems){
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}
