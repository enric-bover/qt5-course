#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:



    void on_addRowButton_clicked();

    void on_removeRowButton_clicked();

    void on_addColumnButton_clicked();

    void on_removeColumnButton_clicked();

    void on_addChildButton_clicked();

private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
