#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
#include <iomanip>

class Board
{
    char board[4][4];
    char users[2] = {'x','o'};
    int turn;
    int xPos, yPos;
    int checkRows(char user);
    int checkCols(char user);
    int checkDiag(char user);
    int checkAll(char user);
    int checkWinner();
    int checkDraw();
    void makeAction();
    void setPosition();
    void swapTurn();
    int isValidPosition();
    void resetPosition();

    public:
    Board();
    void print();
    void test();
    void run();

};

Board::Board()
{
    turn = 0;
    resetPosition();
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++) board[i][j]='-';
    }
}

void Board::test()
{
    std::cout<<turn;
    swapTurn();
    std::cout<<turn;
    swapTurn();
    std::cout<<turn;
    swapTurn();
    std::cout<<turn;
}
void Board::resetPosition()
{
    xPos=-1;
    yPos=-1;
}
void Board::setPosition()
{
    std::cout<<"choose position: "<<std::endl;
    std::cin>>xPos;
    std::cin>>yPos;
//    std::cout<<xPos<<","<<yPos<<std::endl<<std::endl;
    xPos--;
    yPos--;
}

int Board::isValidPosition()
{
    if(xPos<4 && xPos>=0 && yPos<4 && yPos>=0 && board[xPos][yPos]=='-') return 1;
    std::cout<<"choose a place between 1 and 4, and not selected before"<<std::endl;
    return 0;
}


void Board::swapTurn()
{
    turn = !turn;
}


void Board::makeAction()
{
    char user = users[turn];
    setPosition();
    while (!isValidPosition()) {
        setPosition();
    }
    board[xPos][yPos] = user;
    swapTurn();
}

int Board::checkRows(char user)
{
    for(int i=0; i<4; i++)
    {
        int count=0;
        for(int j=0; j<4; j++)
        {
            if(board[i][j]==user) count++;
        }
        if(count==4) return 1;
    }
    return 0;
}

int Board::checkCols(char user)
{
    for(int i=0; i<4; i++)
    {
        int count=0;
        for(int j=0; j<4; j++)
        {
            if(board[j][i]==user) count++;
        }
        if(count==4) return 1;
    }
    return 0;
}

int Board::checkDiag(char user)
{
    int count=0;
    for(int i=0; i<4; i++)
    {
        if(board[i][i]==user) count++;
        if(count==4) return 1;
    }
    return 0;
}

int Board::checkAll(char user)
{
    int result = checkRows(user) || checkCols(user) || checkDiag(user);
    return result;
}

int Board::checkWinner()
{
    for(int i=0; i<2; i++)
    {
        if(checkAll(users[i]))
        {
            std::cout<<"Hooray! ...... "<<users[i]<<" wins!"<<std::endl;
            return 1;
        }
    }
    return 0;
}

int Board::checkDraw()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(board[i][j]=='-') return 0;
        }
    }
    std::cout<<"It's a tie! ........ Let's play again."<<std::endl;
    return 1;
}

void Board::run()
{
    while(!(checkWinner() || checkDraw()))
    {
        makeAction();
        print();
    }
    print();
}

void Board::print()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++) std::cout<<std::setw(5)<<board[i][j];
        std::cout<<std::endl;
    }
}

#endif // TICTACTOE_H
