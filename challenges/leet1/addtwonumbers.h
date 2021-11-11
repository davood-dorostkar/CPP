#ifndef ADDTWONUMBERS_H
#define ADDTWONUMBERS_H
#include <iostream>
using std::cout;
using std::endl;

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        cout << "running add two numbers func..." << endl;
        int num1 = merge(l1);
        int num2 = merge(l2);
        return expand(num1 + num2);
    }
    int merge(ListNode* input)
    {
        ListNode* l = input;
        int result =0;
        int r = 1;
        while(l->val != 0 || l->next != nullptr)
        {
            result += (l->val * r);
            l = l->next;
            r *= 10;
            cout << result << endl;
        }
        return result;
    }

    ListNode* expand(int input)
    {
        ListNode* result = new ListNode();
        int i = 0;
        while(input % 10 != 0)
        {
            ListNode* node = new ListNode(input % 10);
            (result+i)->next = node;
            input /= 10;
            ++i;

        }
        return result;
    }
};
#endif // ADDTWONUMBERS_H
