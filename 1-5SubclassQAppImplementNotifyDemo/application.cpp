#include "application.h"
#include <QDebug>
#include "widget.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{

}


bool Application::notify(QObject *destination, QEvent *event)
{

    if( event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick){
        qDebug() << " Application : mouse press or double click detected";

        qDebug() << "Class name : " << destination->metaObject()->className();

        Widget *button = dynamic_cast<Widget* >(destination);
        if(button){
            qDebug() << "Cast successful";
        }else{
            qDebug() << "Cast failed";
        }

        return false;
    }

    return QApplication::notify(destination, event);
}
