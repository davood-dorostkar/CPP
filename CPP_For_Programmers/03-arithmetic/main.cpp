#include <QCoreApplication>
//#include "calc.h"
#include "polynomial.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    Calc* calc = new Calc;
//    calc->shapesVolume();
    Polynomial* poly = new Polynomial;
    poly->solve();

    return a.exec();
}
