#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QMessageBox>
#include "persondelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    PersonDelegate * personDelegate = new PersonDelegate(this);
    model = new PersonModel(this);

    ui->listView->setModel(model);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(2, personDelegate);
    ui->treeView->setModel(model);
    ui->treeView->setItemDelegate(personDelegate);

    ui->tableView->setSelectionModel(ui->listView->selectionModel());
    ui->treeView->setSelectionModel(ui->listView->selectionModel());

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_addPersonButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(nullptr, "Names", tr("Person name:"), QLineEdit::Normal, "Type in name", &ok);

    if (ok && !name.isEmpty()){
        int age = QInputDialog::getInt(nullptr, "Person Age", "Age",20,15,120);

        Person * person = new Person(name, "blue", age, this);

        model->addPerson(person);
    }
    else{
        QMessageBox::information(nullptr, "Failure", "Must specify name and age");
    }
}


void Widget::on_removePersonButton_clicked()
{

    QModelIndex index = ui->listView->currentIndex();
    model->removePerson(index);

}

