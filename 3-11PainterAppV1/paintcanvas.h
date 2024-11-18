#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include <QWidget>

class PaintCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit PaintCanvas(QWidget *parent = nullptr);

signals:

};

#endif // PAINTCANVAS_H
