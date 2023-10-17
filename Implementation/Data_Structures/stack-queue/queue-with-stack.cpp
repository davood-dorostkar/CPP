#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
//#include <queue>
#include <stack>

using namespace std;


class Queue
{
    stack<int> temp,real;
    int queueSize;
    int _front;
    int _back;
public:
    Queue():queueSize(0){}
    ~Queue(){}

    void push(int val)
    {
        _back=val;
        if(queueSize==0)
            _front=val;
        real.push(val);
        queueSize++;

    }

    void pop()
    {
        if(queueSize==0)
        {
            cout<<"queue is already empty"<<endl;
            return;
        }
        while(real.size()>1)
        {
            if(real.size()==2)
                _front=real.top();
            temp.push(real.top());
            real.pop();
        }
        real.pop();
        while(temp.size()>0)
        {
            if(temp.size()==1)
                _back=temp.top();
            real.push(temp.top());
            temp.pop();
        }
        queueSize--;
    }

    int size()
    {
        return queueSize;
    }

    int isEmpty()
    {
        return (queueSize==0);
    }

    int front()
    {
        return _front;
    }

    int back()
    {
        return _back;
    }
};

int main()
{
    Queue qu;
    qu.push(1);
    qu.push(2);
    qu.push(3);
    qu.push(4);
    cout<<qu.front()<<endl;
    cout<<qu.back()<<endl;
    qu.pop();
    cout<<qu.front()<<endl;
    cout<<qu.back()<<endl;
    cout<<"empty? "<<qu.isEmpty()<<endl;
    return 0;
}
