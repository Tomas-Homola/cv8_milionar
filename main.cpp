#include "cv8_milionar.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    QApplication a(argc, argv);
    cv8_milionar w;
    w.show();
    return a.exec();
}
