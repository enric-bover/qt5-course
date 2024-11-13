#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::paintEvent(QPaintEvent *event)
{
    QPen mPen(Qt::red);
    mPen.setWidth(3);

    QPainter painter(this);  // this is the device that we will be painting on

    painter.setPen(mPen);

    qDebug() << "Logical coordinates : " << painter.window();
    qDebug() << "Physical coordinates : " << painter.viewport();

    // Change the logical coordinates

    painter.drawRect(50,50,100,100);


    painter.save();

    painter.setWindow(0,0,300,200);
    mPen.setColor(Qt::green);
    painter.setPen(mPen);

    painter.drawRect(50,50,100,100);


    painter.restore();
}
