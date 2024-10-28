#include "childbutton.h"
#include <QDebug>

ChildButton::ChildButton(QWidget *parent) : ParentButton(parent)
{

}


void ChildButton::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "ChildButton mousePresEvent called";
    //ParentButton::mousePressEvent(event);
}
