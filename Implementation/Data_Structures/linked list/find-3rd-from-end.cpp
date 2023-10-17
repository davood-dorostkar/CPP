#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int val): value(val),next(nullptr){}
};

Node* AddNode(Node* node, int val)
{
    Node* newNode = new Node(val);
    node->next = newNode;
    return newNode;
}

Node* find3rdFromLast(Node* head)
{
    Node* current = head;
    if(current->next==nullptr || current->next->next==nullptr)
    {
        cout << "linked list too short" << endl;
        return current;
    }
    while(current->next->next->next!=nullptr)
    {
        current=current->next;
    }
    return current;
}

int main()
{
    Node* head = new Node(0);
    Node* node1 = AddNode(head,1);
    Node* node2 = AddNode(node1,2);
    Node* node3 = AddNode(node2,3);
    Node* node4 = AddNode(node3,4);

    Node* result = find3rdFromLast(head);
    cout << result->value;
    return 0;
}
