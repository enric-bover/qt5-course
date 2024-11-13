#include "widget.h"
#include "ui_widget.h"
#include "indicator.h"
#include "tank.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    QObject::connect(ui->waterTank, &tank::normal, ui->indicator, &Indicator::activateNormal);
    QObject::connect(ui->waterTank, &tank::warning, ui->indicator, &Indicator::activateWarning);
    QObject::connect(ui->waterTank, &tank::danger, ui->indicator, &Indicator::activateDanger);

}

Widget::~Widget()
{
    delete ui;
}

