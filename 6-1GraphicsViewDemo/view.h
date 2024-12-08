#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // VIEW_H
