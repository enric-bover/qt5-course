#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    scene = new QGraphicsScene(this);
    scene->addLine(-400,0,400,0,QPen(Qt::blue));
    scene->addLine(0,-400,0,400,QPen(Qt::blue));

    scene->setSceneRect(-800,-400,1600,800);


    QGraphicsView * view = new QGraphicsView(this);

    QGraphicsRectItem * redRect = scene->addRect(0,0,200,100);
    redRect->setPen(Qt::NoPen);
    redRect->setFlag(QGraphicsItem::ItemIsSelectable);
    redRect->setBrush(QBrush(Qt::red));


    view->setScene(scene);



    ui->viewLayout->addWidget(view);


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_xTranslateSpinbox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){
        QTransform transform = item->transform();
        transform.translate(arg1 - transform.dx(),0);

        item->setTransform(transform);
    }
}


void Widget::on_yTranslateSpinbox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){
        QTransform transform = item->transform();
        transform.translate(0,arg1 - transform.dy());

        item->setTransform(transform);
    }
}


void Widget::on_xScaleSpinbox_valueChanged(int arg1)
{

    QGraphicsItem * item = getSelectedItem();
    if(item){
        QTransform transform = item->transform();
        double scaleFactor = arg1/transform.m11();
        transform.scale(scaleFactor, 1);

        item->setTransform(transform);

    }
}


void Widget::on_yScaleSpinbox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){
        QTransform transform = item->transform();
        double scaleFactor = arg1/transform.m22();
        transform.scale(1, scaleFactor);

        item->setTransform(transform);

    }
}


void Widget::on_xShearSpinbox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){

    }
}


void Widget::on_yShearSpinbox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){

    }
}


void Widget::on_rotationSpinBox_valueChanged(int arg1)
{
    QGraphicsItem * item = getSelectedItem();
    if(item){

    }
}

QGraphicsItem *Widget::getSelectedItem()
{
    if(scene->selectedItems().count()>0){
        return scene->selectedItems().at(0);
    }
    return nullptr;
}

