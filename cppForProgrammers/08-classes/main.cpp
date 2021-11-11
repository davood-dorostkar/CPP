#include <QCoreApplication>
//#include "gameboardsearch.h"
//#include "classarray.h"
//#include "tictactoe.h"
#include "classroom.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Classroom classroom;
    classroom.analysis();

//    Board board;
//    board.run();

//    gameSearch();

//    const int SIZE=3;
//    Dog roster[SIZE];
//    roster[0].setName("Blue");
//    roster[1].setName("King");
//    roster[2].setName("Spot");
//    printRoster(roster,SIZE);
    return a.exec();
}
