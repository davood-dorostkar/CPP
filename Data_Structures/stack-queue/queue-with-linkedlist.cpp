#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
//#include <stack>

using namespace std;

class Node
{
public:
    int value;
    Node* next;
    Node(int val):value(val),next(nullptr){}
};

class Queue
{
    Node* _back;
    Node* _front;
    int _queueSize;

public:
    Queue()
    {
    _back= nullptr;
    _front= nullptr;
    _queueSize=0;
    }
    ~Queue()
    {
        while (_queueSize>0)
        {
            Node* temp = _front;
            _front = _front->next;
            delete temp;
            _queueSize--;
        }
    }

    void push(int val)
    {
        Node* newNode = new Node(val);
        if(this->isEmpty())
        {
            _front = newNode;
            _back = newNode;
        }
        else
        {
            _back->next = newNode;
            _back = newNode;

        }
        _queueSize++;
    }

    void pop()
    {
        if(this->isEmpty())
            cout<<"queue is empty"<<endl;
        else
        {
            Node* temp = _front;
            _front = _front->next;
            delete  temp;
            _queueSize--;
        }

    }

    int size()
    {
        return _queueSize;
    }

    int isEmpty()
    {
        return (_back==nullptr);
    }

    int front()
    {
        return _front->value;
    }

    int back()
    {
        return _back->value;
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
