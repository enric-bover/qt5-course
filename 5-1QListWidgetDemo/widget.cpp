#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->listWidget->setIconSize(QSize(70,70));
    fruitsList << "Apple" << "Avocado" << "Banana"
               << "Blueberries" << "Cucumber" << "EggFruit"
               << "Fig" << "Grape" << "Mango" << "Pear"
               << "Pineapple" << "Watermellon";

    foreach(QString fruit, fruitsList){
        QListWidgetItem * item = new QListWidgetItem(fruit,ui->listWidget);
        QString filename = ":/images/" + fruit.toLower() + ".png";
        item->setIcon(QIcon(filename));
        item->setData(Qt::UserRole, fruit);
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_readDataButton_clicked()
{
    QString fruit = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    qDebug() << "Current fruit : " << fruit;
}

