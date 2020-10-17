#include "widget.h"
#include "ekgwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EkgWidget ekg;
    ekg.show();

    Widget w;
    w.show();

    return a.exec();
}
