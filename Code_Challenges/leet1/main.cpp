#include <iostream>
#include "addtwonumbers.h"

using namespace std;

int main()
{
    Solution s;
    ListNode* n1 = new ListNode(0);
    ListNode* n2 = new ListNode(0);
    ListNode* n3 = new ListNode(2);
    n1->next = n2;
    n2->next = n3;
    ListNode* m1 = new ListNode(5);
    ListNode* m2 = new ListNode(5);
    ListNode* m3 = new ListNode(5);
    ListNode* m4 = new ListNode(5);
    m1->next = m2;
    m2->next = m3;
    m3->next = m4;
//    ListNode* result  = s.expand(0);
    ListNode* result = s.addTwoNumbers(n1, m1);
//    ListNode node = ListNode();
//    s.printList(&node);
//    ListNode* result = s.addTwoNumbers(&node, &node);
    s.printList(result);
    return 0;
}
