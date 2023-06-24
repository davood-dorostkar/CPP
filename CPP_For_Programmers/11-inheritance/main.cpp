#include <QCoreApplication>
#include <iostream>
#include "flower.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Rose r;
    r.setBloom("spring");
    r.setFragrance("strong");
    std::cout << r.getBloom() << ", " << r.getFragrance() << std::endl;
    return a.exec();
}
