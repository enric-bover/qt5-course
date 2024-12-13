#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap mPixmap):
    wingPosition(WingPosition::Up),
    wingDirection(0)
{
    setPixmap(mPixmap);

    birdWingsTimer = new QTimer(this);
    QObject::connect(birdWingsTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    birdWingsTimer->start(80);

    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this,"y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    //rotateTo(90,1200,QEasingCurve::InQuad);

    //yAnimation->start();
}

void BirdItem::updatePixmap()
{
    if(wingPosition == WingPosition::Middle){
        if(wingDirection){
            //UP
            setPixmap(QPixmap(":/images/bird_blue_up.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        } else{
            //DOWN
            setPixmap(QPixmap(":/images/bird_blue_down.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }
    } else{
        setPixmap(QPixmap(":/images/bird_blue_middle.png"));
        wingPosition = WingPosition::Middle;
    }
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

void BirdItem::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(newRotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::setY(qreal newY)
{
    moveBy(0,newY-m_y);
    m_y = newY;

}

void BirdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);
    yAnimation->start();

    QObject::connect(yAnimation, &QPropertyAnimation::finished,[=](){
        fallToGroundIfNecessary();
    });

    rotateTo(-20,200,QEasingCurve::OutCubic);

}

void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);

}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::fallToGroundIfNecessary()
{
    if (y() < groundPosition){
        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90,1200,QEasingCurve::InQuad);

    }
}
