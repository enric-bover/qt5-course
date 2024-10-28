#include "parentlineedit.h"
#include <QDebug>

ParentLineEdit::ParentLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}


void ParentLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "ParentLineEdit keyPresseEvent";
    QLineEdit::keyPressEvent(event);
}
