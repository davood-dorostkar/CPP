#include <iostream>
#include "addtwonumbers.h"

using namespace std;

int main()
{
    Solution s;
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(4);
    ListNode* n3 = new ListNode(3);
    n1->next = n2;
    n2->next = n3;
    ListNode* m1 = new ListNode(5);
    ListNode* m2 = new ListNode(1);
    ListNode* m3 = new ListNode(9);
    m1->next = m2;
    m2->next = m3;
    s.merge(n1);
    s.merge(n2);
//    s.addTwoNumbers(n1, n2);
    return 0;
}
