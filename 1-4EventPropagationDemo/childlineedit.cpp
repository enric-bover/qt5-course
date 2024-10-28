#include "childlineedit.h"
#include <QDebug>
#include <QKeyEvent>

ChildLineEdit::ChildLineEdit(QWidget *parent)
    : ParentLineEdit(parent)
{

}


void ChildLineEdit::keyPressEvent(QKeyEvent *event)
{
    //    qDebug() << "ChildLineEdit keypressEvent";
    //    ParentLineEdit::keyPressEvent(event);

    qDebug() << event->isAccepted();

    if(event->key() == Qt::Key_Delete){
        qDebug() << "Pressed the Delete Key";
        clear();
    } else{
        ParentLineEdit::keyPressEvent(event);
    }
}
