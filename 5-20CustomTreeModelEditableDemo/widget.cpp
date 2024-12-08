#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>
#include "personmodel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    PersonModel * model = new PersonModel(this);
    ui->treeView->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_addRowButton_clicked()
{

    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel * model = ui->treeView->model();

    if(!model->insertRow(index.row()+1, index.parent()))
        return;

    for(int column = 0; column < model->columnCount(index.parent()); ++column){
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[Empty Cell]"), Qt::EditRole);
    }
}


void Widget::on_removeRowButton_clicked()
{

}


void Widget::on_addColumnButton_clicked()
{

}


void Widget::on_removeColumnButton_clicked()
{

}


void Widget::on_addChildButton_clicked()
{

}

