#ifndef SHAPECANVAS_H
#define SHAPECANVAS_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>

class ShapeCanvas : public QWidget
{
    Q_OBJECT
public:

    enum Shape{
        Polygon,
        Rect,
        RoundedRect,
        Ellipse,
        Pie,
        Chord,
        Text,
        Pixmap
    };
    explicit ShapeCanvas(QWidget *parent = nullptr);



    Shape getShape() const;
    void setShape(Shape newShape);

    QPen getPen() const;
    void setPen(const QPen &newPen);

    QBrush getBrush() const;
    void setBrush(const QBrush &newBrush);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;
    Shape shape;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;

    // QWidget interface
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool getAntialiased() const;
    void setAntialiased(bool newAntialiased);
    bool getTransformed() const;
    void setTransformed(bool newTransformed);
};

#endif // SHAPECANVAS_H
