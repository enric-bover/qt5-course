#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    enum ToolType{
        Cursor,
        Pen,
        Rect,
        Ellipse,
        Star,
        QtQuick,
        Eraser
    };

    ToolType getTool() const;
    void setTool(ToolType newTool);

signals:

public slots:

    // QGraphicsScene interface
protected:
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;



private:

    void drawLineTo(const QPointF &endPoint);
    QPointF startingPoint;
    QPointF lastPenPoint;
    ToolType tool;
    bool drawing;
    QGraphicsItemGroup * lineGroup;
};

#endif // SCENE_H
