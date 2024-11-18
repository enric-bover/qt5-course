#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "shapecanvas.h"


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
    void on_shapeCombo_activated(int index);

    void on_penWidth_valueChanged(int arg1);

    void on_penStyleCombobox_activated(int index);

    void on_penCapComboBox_activated(int index);

    void on_penJoinComboBox_activated(int index);

    void on_brushStyleComboBox_activated(int index);

    void on_antiCheckBox_toggled(bool checked);

    void on_transformCheckBox_toggled(bool checked);

    void penChanged();
    void brushChanged();

private:
    Ui::Widget *ui;
    ShapeCanvas * canvas;

};
#endif // WIDGET_H
