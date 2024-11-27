#include "container.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDataStream>
#include <QMimeData>
#include <QDrag>

Container::Container(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(150,150);

    setAcceptDrops(true);

    QLabel * qtIcon = new QLabel(this);
    qtIcon->setPixmap(QPixmap(":/images/qt.png"));
    qtIcon->move(20,20);
    qtIcon->show();
    qtIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel * cppIcon = new QLabel(this);
    cppIcon->setPixmap(QPixmap(":/images/cpp.png"));
    cppIcon->move(150,20);
    cppIcon->show();
    cppIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel * terminalIcon = new QLabel(this);
    terminalIcon->setPixmap(QPixmap(":/images/terminal.png"));
    terminalIcon->move(20,150);
    terminalIcon->show();
    terminalIcon->setAttribute(Qt::WA_DeleteOnClose);
}


void Container::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
        startPos = event->pos();
    QWidget::mousePressEvent(event);
}

void Container::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        int distance = (event->pos() - startPos).manhattanLength();
        if(distance >= QApplication::startDragDistance()){
            QLabel * child = static_cast<QLabel *>(childAt(event->pos()));

            if(!child)
                return;

            QPixmap mPixmap = child->pixmap(Qt::ReturnByValue);
            QByteArray ba;
            QDataStream dataStream(&ba, QIODevice::WriteOnly);

            dataStream << mPixmap << QPoint(event->pos() - child->pos());

            QMimeData * mimeData = new QMimeData();
            mimeData->setData("application/x-qtcustomitem", ba);

            QDrag * drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(mPixmap);


            drag->setHotSpot(event->pos() - child->pos());

            //blur the orignal label

            QPixmap tempPix = mPixmap;
            QPainter painter(&tempPix);
            painter.fillRect(tempPix.rect(), QColor(127, 127, 127, 127));

            child->setPixmap(tempPix);


            if(drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction){
                child->close();

            }else{
                child->setPixmap(mPixmap);

            }
        }
    }

}

void Container::dragEnterEvent(QDragEnterEvent *event)
{
}

void Container::dragMoveEvent(QDragMoveEvent *event)
{
}

void Container::dragLeaveEvent(QDragLeaveEvent *event)
{
}

void Container::dropEvent(QDropEvent *event)
{
}


void Container::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundRect(0,5,width()-10, height()-10,3,3);
    QWidget::paintEvent(event);

}
