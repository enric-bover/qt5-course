#include "widget.h"
#include "ui_widget.h"
#include "indicator.h"
#include "tank.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Indicator * indicator = new Indicator(this);
    tank * tankk = new tank(this);

    ui->horizontalLayout->addWidget(tankk);
    ui->horizontalLayout->addWidget(indicator);

    QObject::connect(tankk, &tank::normal, indicator, &Indicator::activateNormal);
    QObject::connect(tankk, &tank::warning, indicator, &Indicator::activateWarning);
    QObject::connect(tankk, &tank::danger, indicator, &Indicator::activateDanger);

}

Widget::~Widget()
{
    delete ui;
}

