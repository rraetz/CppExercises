#include "widget.h"
#include "ekgwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    EkgWidget ekg;
    ekg.show();

    return a.exec();
}
