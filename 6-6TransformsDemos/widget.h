#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

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
    void on_xTranslateSpinbox_valueChanged(int arg1);

    void on_yTranslateSpinbox_valueChanged(int arg1);

    void on_xScaleSpinbox_valueChanged(int arg1);

    void on_yScaleSpinbox_valueChanged(int arg1);

    void on_xShearSpinbox_valueChanged(int arg1);

    void on_yShearSpinbox_valueChanged(int arg1);

    void on_rotationSpinBox_valueChanged(int arg1);

private:
    Ui::Widget *ui;

    QGraphicsItem * getSelectedItem();
    QGraphicsScene * scene;
};
#endif // WIDGET_H
