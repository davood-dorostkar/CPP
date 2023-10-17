#include <iostream>
#include <vector>
#include <unordered_map>

struct Node
{
    int value;
    Node* next;
    Node(int val): value(val),next(nullptr){}
};


Node* addNode(Node* node,int val)
{
    Node* newNode = new Node(val);
    node->next = newNode;
    return newNode;
}


Node* findMiddle(Node* head)
{
    Node* slow = head;
    Node* fast = head;
    while (fast->value!=NULL && fast->next!=nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    std::cout << slow->value << " " << slow << std::endl;
    return slow;
}

int main()
{
    Node* head = new Node(1);
    Node* node1 = addNode(head, 2);
    Node* node2 = addNode(node1, 3);
    Node* node3 = addNode(node2, 4);
    Node* node4 = addNode(node3, 5);
    Node* node5 = addNode(node4, 6);
    Node* node6 = addNode(node5, 7);

    findMiddle(head);
    return 0;
}
