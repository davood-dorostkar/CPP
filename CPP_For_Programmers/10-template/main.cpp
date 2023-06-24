#include <QCoreApplication>
#include "templates.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testTemplate();
    return a.exec();
}
