#include "aed_display.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AED_Display w;
    w.show();
    return a.exec();
}

