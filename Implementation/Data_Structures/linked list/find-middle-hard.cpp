#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class Person
{
public:
    int _age;
    std::string _name;
    Person(std::string name,int age)
    {
        _age =age;
        _name = name;
    }

};


template <typename type>
struct Node
{
    type value;
    Node* next;
    Node(type val): value(val),next(nullptr){}
};

template <typename type>
Node<type>* addNode(Node<type>* node,type val)
{
    Node<type>* newNode = new Node<type>(val);
    node->next = newNode;
    return newNode;
}

template <typename type>
Node<type>* findMiddle(Node<type>* head)
{
    Node<type>* slow = head;
    Node<type>* fast = head;
    // you can choose between fast!=nullptr or fast->next->next!=nullptr
    // to decide the middle item when the length of list is EVEN
    while (fast!=nullptr && fast->next!=nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    std::cout << slow->value._name << " " << slow << std::endl;
    return slow;
}

int main()
{
    Node<Person>* head = new Node<Person>(Person("david",1));
    Node<Person>* node1 = addNode(head, Person("jane", 2));
    Node<Person>* node2 = addNode(node1,  Person("mike", 3));
    Node<Person>* node3 = addNode(node2, Person("joe", 4));
    Node<Person>* node4 = addNode(node3, Person("jack", 5));
    Node<Person>* node5 = addNode(node4, Person("fred", 6));
    Node<Person>* node6 = addNode(node5, Person("tom", 7));

    findMiddle(head);
    return 0;
}
