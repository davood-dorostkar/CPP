#include <QCoreApplication>
#include <iostream>


void swap(int &x, int &y)
{
    x = x + y;
    y = x - y;
    x = x - y;
}

void print(int x, int y)
{
    std::cout << "x: " << x << " ,y: " << y << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int x = 10, y = 54;
    print(x,y);
    swap(x,y);
    print(x,y);
    return a.exec();
}
