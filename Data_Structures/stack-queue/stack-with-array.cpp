#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>

//#include <stack>

using namespace std;


class stack
{
    static const int stackSize = 100;
    int array[100];
    int cursor;

public:
    stack()
    {
        cursor=-1;
    }
    ~stack(){}

    void push(int val)
    {
        if(isFull())
        {
            cout<<"you cannot add to a full stack"<<endl;
            return;
        }
        cursor++;
        array[cursor]=val;
    }

    void pop()
    {
        if(cursor>=0)
            cursor--;
        else
            cout<<"there is no more data in the stack"<<endl;
    }

    int size()
    {
        return (cursor+1);
    }

    int top()
    {
        if(cursor>=0)
            return array[cursor];
        else
            cout<<"there is no data in the stack"<<endl;
        return -1;
    }

    int isEmpty()
    {
        return (cursor==-1);
    }

    int isFull()
    {
        return (cursor==stackSize-1);
    }
};

int main()
{
    stack mystask;
    mystask.push(1);
    mystask.push(3);
    mystask.push(6);
    mystask.push(9);
    cout << mystask.top()<<endl;
    cout << mystask.size()<<endl;
    mystask.pop();
    mystask.pop();
    mystask.pop();
    mystask.pop();
    mystask.pop();
    cout << mystask.isEmpty()<<endl;
    cout << mystask.top()<<endl;
    return 0;
}
