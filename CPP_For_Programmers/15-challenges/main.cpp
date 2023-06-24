#include <QCoreApplication>
#include <iostream>
#include "challenges.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << Factorial(6) << std::endl;
    return a.exec();
}
