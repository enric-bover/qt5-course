#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>

class StarEditor : public QWidget
{
    Q_OBJECT
public:
    explicit StarEditor(QWidget *parent = nullptr);

signals:
    void editingFinished();

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    int starRating;
    QPolygon poly;

    // QWidget interface
public:
    QSize sizeHint() const override;
    int getStarRating() const;
    void setStarRating(int newStarRating);
};



#endif // STAREDITOR_H
