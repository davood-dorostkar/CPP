#include <QCoreApplication>
#include "loops.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Loops* calc = new Loops;
    calc->whileGuess();
    return a.exec();
}
