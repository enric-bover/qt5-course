#include "widget.h"
#include "filter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    Filter * filter = new Filter(&w);
    a.installEventFilter(filter);


    w.show();
    return a.exec();
}
