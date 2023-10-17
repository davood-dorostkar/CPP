#include <iostream>

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

Node* findNthFromLast(Node* head,int num)
{
    Node* slow = head;
    Node* fast = head;
    for (int i = 1; i <= num; i++)
    {
        if(fast==nullptr || fast->next==nullptr)
        {
            cout << "Linked list too short" << endl;
            return head;
        }
        fast = fast->next;
    }

    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

int main() {
    Node* head = new Node(0);
    Node* node1 = addNode(head, 1);
    Node* node2 = addNode(node1, 2);
    Node* node3 = addNode(node2, 3);
    Node* node4 = addNode(node3, 4);

    Node* result = findNthFromLast(head,4);
    cout << "Value of 3rd node from last: " << result->value << endl;

    Node* current = head;
    while (current->next != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
