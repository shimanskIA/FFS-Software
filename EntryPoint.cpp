#include "FFSDatabaseInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FFSDatabaseInterface w;
    w.show();
    return a.exec();
}
