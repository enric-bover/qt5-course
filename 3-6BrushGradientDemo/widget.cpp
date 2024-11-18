#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

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
    QPainter painter(this);

    QLinearGradient linearGradient(QPoint(70,20), QPoint(70,170));
    linearGradient.setColorAt(0,Qt::red);
    linearGradient.setColorAt(1, Qt::yellow);

    QBrush mBrush(linearGradient);
    painter.setBrush(mBrush);
    painter.drawRect(20,20,100,300);
}
