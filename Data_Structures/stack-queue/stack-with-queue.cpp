#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
//#include <stack>

using namespace std;


class stack
{
    queue<int> temp,real;
    int stackSize=0;

public:
    stack()
    {

    }
    ~stack(){}

    void push(int val)
    {
        real.push(val);
        stackSize++;
    }

    void pop()
    {
        for(int i=0; real.size()-2; i++)
        {
            temp.push(real.front());
        }
        swap(temp,real);
        stackSize--;
        return temp.pop();
    }

    int size()
    {
        return stackSize;
    }

    int top()
    {
        for(int i=0; real.size()-1; i++)
        {
            temp.push(real.front());
            real.pop();
        }
        int result = real.front();
        temp.push(real.front());
        swap(temp,real);
        return result;
    }

    int isEmpty()
    {
        return (stackSize==0);
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
//    cout << mystask.size()<<endl;
//    mystask.pop();
//    mystask.pop();
//    mystask.pop();
//    mystask.pop();
//    mystask.pop();
//    cout << mystask.isEmpty()<<endl;
//    cout << mystask.top()<<endl;
    return 0;
}
