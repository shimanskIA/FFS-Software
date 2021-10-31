#include "FFSDatabaseInterface.h"
#include "DbConnection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbConnection::GetDbConnectionInstance();
    FFSDatabaseInterface w;
    w.show();
    return a.exec();
}
