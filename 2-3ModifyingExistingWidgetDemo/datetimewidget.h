#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QTimer>

class DateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = nullptr);

signals:

private:
    QTimer * timer;
    QLabel * labelTop;
    QLabel * labelBottom;
    QString dateString;
    QString timeString;

public slots:
    void updateTime();

};

#endif // DATETIMEWIDGET_H
