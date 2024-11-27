#ifndef WIDGET_H
#define WIDGET_H

#include "dragdroplabel.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    DragDropLabel * dragDropLabel;

private slots:
    void mimeChanged(const QMimeData * mimeData);
    void on_clearButton_clicked();
};
#endif // WIDGET_H
