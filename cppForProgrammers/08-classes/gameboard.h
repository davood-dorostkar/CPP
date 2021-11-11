#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <iomanip>
using namespace std;

class Gameboard
{
    char gameSpace[4][4];
public:
    Gameboard();
    void setGameSpace(int row,int column, char value);
    char getGameSpace(int row,int column);
    int fourInRow();
    void printInfo();
};

Gameboard::Gameboard()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gameSpace[i][j]='-';
        }
    }
}

void Gameboard::setGameSpace(int row, int col, char val)
{
    gameSpace[row][col]=val;
}

char Gameboard::getGameSpace(int row, int col)
{
    return gameSpace[row][col];
}

int Gameboard::fourInRow()
{
    for(int i=0; i<4; i++)
    {
        int times=0;
        for(int j=0; j<4; j++)
        {
            if(gameSpace[i][j]=='x') times++;
        }
        if(times==4) return 1;
    }
    return 0;
}

void Gameboard::printInfo()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout<<setw(5)<<gameSpace[i][j];
        }
        cout<<endl;
    }
}
#endif // GAMEBOARD_H
