#ifndef TANK_H
#define TANK_H

#include <QWidget>
#include <QTimer>

class tank : public QWidget
{
    Q_OBJECT
public:
    explicit tank(QWidget *parent = nullptr);

signals:
    void normal();
    void warning();
    void danger();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    // QWidget interface
public:
    QSize sizeHint() const override;

private:
    int waterHeight;
    QTimer * timer;

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // TANK_H
