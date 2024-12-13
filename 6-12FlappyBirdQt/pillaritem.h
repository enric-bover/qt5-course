#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;
    void setX(qreal newX);

signals:
    void CollideFail();

private:
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;


    qreal m_x;
    int yPos;

    bool CollidesWithBird();

};

#endif // PILLARITEM_H
