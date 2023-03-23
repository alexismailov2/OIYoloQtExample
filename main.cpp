#include <QApplication>

#include "OIYoloWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OIYoloWindow w(false);
    w.show();
    return QApplication::exec();
}

