#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
//#include <stack>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int val):value(val){}
};

class stack
{
    Node* head;
    int stackSize;

public:
    stack():head(nullptr),stackSize(0){}
    ~stack()
    {
        while(head!=nullptr) pop();
    }

    void push(int val)
    {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        stackSize++;
     }

    void pop()
    {
        if(head==nullptr)
        {
            cout << "stack is already empty"<<endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        stackSize--;
    }

    int size()
    {
        return stackSize;
    }

    int top()
    {
        if(head!=nullptr)
            return head->value;
        else
        {
            cout<<"you cannot get an empty stack"<<endl;
            return -1;
        }
    }

    int isEmpty()
    {
        return (head==nullptr);
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
