#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include <QWidget>

class PaintCanvas : public QWidget
{
    Q_OBJECT
public:
    enum ToolType{Pen, Rect, Ellipse, Eraser};
    explicit PaintCanvas(QWidget *parent = nullptr);

    ToolType getTool() const;
    void setTool(ToolType newTool);

    bool getFill() const;
    void setFill(bool newFill);

    int getPenWidth() const;
    void setPenWidth(int newPenWidth);

    QColor getFillColor() const;
    void setFillColor(const QColor &newFillColor);

    QColor getPenColor() const;
    void setPenColor(const QColor &newPenColor);

    QPoint getLastPoint() const;
    void setLastPoint(QPoint newLastPoint);

signals:

private:

    void drawLineTo(const QPoint &endPoint);
    void drawRectTo(const QPoint & endPoint, bool elipse = false);
    void eraseUnder(const QPoint & topeLeft);

    void resizeImage(QImage *image, const QSize &newSize);

    ToolType tool;
    bool fill;
    bool drawing;
    int penWidth;
    QColor fillColor;
    QColor penColor;
    QPoint lastPoint;
    QRectF lastRect;
    QImage image;







    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // PAINTCANVAS_H
