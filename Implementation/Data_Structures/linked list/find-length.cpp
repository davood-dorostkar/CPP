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


int length(Node* head)
{
    if (head == nullptr) return 0;
    int len=1;
    while(head->next!=nullptr)
    {
        len++;
        head = head->next;
    }
    return len;
}

int main()
{
    Node* head = new Node(0);
    Node* node1 = addNode(head, 1);
    Node* node2 = addNode(node1, 2);
    Node* node3 = addNode(node2, 3);
    Node* node4 = addNode(node3, 4);
    cout << length(head) << endl;
    return 0;
}
