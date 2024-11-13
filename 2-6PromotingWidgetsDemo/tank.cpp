#include "tank.h"
#include <QPen>
#include <QPainter>
#include <QWheelEvent>

tank::tank(QWidget *parent)
    : QWidget{parent},
    waterHeight(50), timer(new QTimer(this))
{
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    timer->setInterval(1000);
    QObject::connect(timer, &QTimer::timeout,[=](){
        waterHeight += 15;
        update();

        if(waterHeight <= 210){
            emit normal();
        } else if ((waterHeight>=211) && (waterHeight<=239)){
            emit warning();
        } else{
            emit danger();
        }
    });

    timer->start();
}


void tank::paintEvent(QPaintEvent *event)
{
    QPen mPen;
    mPen.setWidth(3);
    mPen.setColor(Qt::black);

    QPainter painter(this);
    painter.setPen(mPen);

    painter.drawLine(10,10,10,300);
    painter.drawLine(10,300,300,300);
    painter.drawLine(300,300,300,10);

    painter.setBrush(Qt::blue);
    painter.drawRect(10,300-waterHeight, 290, waterHeight);

}


QSize tank::sizeHint() const
{
    return QSize(400,400);

}


void tank::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0 && waterHeight > 10){
        waterHeight -= 10;
        update();
    }
}
