#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {}
};

Node* addNode(Node* node, int val) {
    Node* newNode = new Node(val);
    node->next = newNode;
    return newNode;
}

Node* addNode(Node* prev, Node* next, int val)
{
    Node* newNode = new Node(val);
    prev->next = newNode;
    newNode->next = next;
    return newNode;
}

Node* findLoop(Node* head)
{
    unordered_map<Node*,int> freq;
    while(head->next!=nullptr)
    {
        if(freq[head]<1)
        {
            freq[head]++;
            head = head->next;
        }
        else
        {
            cout << "loop found" << endl;
            return head;
        }
    }
    cout << "no loop" << endl;
    return head;
}

int main() {

    Node* head = new Node(0);
    Node* node1 = addNode(head, 1);
    Node* node2 = addNode(node1, 2);
    Node* node3 = addNode(node2, 3);
    Node* node4 = addNode(node3, 4);
    Node* node5 = addNode(node4,node2, 5);

    cout << findLoop(head)->value << endl;
    cout << head->value << endl;
    return 0;
}
