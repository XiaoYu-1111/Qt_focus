#include "Qt_focus.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_focus w;
    w.show();
    //WavesWidget w2;
    //w2.show();

    return a.exec();
}
