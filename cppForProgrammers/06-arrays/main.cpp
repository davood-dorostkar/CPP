#include <QCoreApplication>
#include "sort.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Sort sort;
    sort.ascending();

    return a.exec();
}
