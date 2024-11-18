#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    QPixmap mPix (width()-10, height() - 10);
    mPix.fill(Qt::gray);

    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::white);

    QFont mFont("Consolas", 20, QFont::Bold);

    QPainter painter(&mPix);
    painter.setPen(pen);
    painter.setBrush(Qt::green);
    painter.setFont(mFont);

    painter.drawRect(50,50,100,100);

    ui->label->setPixmap(mPix);
}

Widget::~Widget()
{
    delete ui;
}

