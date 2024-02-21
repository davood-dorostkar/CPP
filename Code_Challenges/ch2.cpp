#include <iostream>
using std::cout;
using std::endl;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        cout << "Running add two numbers function ..." << endl;
        int num1 = merge(l1);
        int num2 = merge(l2);
        //        cout << num1 << " " << num2 << endl;
        return expand(num1 + num2);
    }
    int merge(ListNode *input)
    {
        ListNode *list = input;
        int result = 0;
        while (list)
        {
            result *= 10;
            result += list->val;
            list = list->next;
        }
        return result;
    }

    ListNode *expand(int input)
    {
        //        cout << "input: " << input << endl;
        ListNode *head = new ListNode();
        ListNode *current = new ListNode();
        //        cout << "head: " << head->val << endl;
        if (input == 0)
            return head;
        //        cout << "input: " << input << endl;
        while (input != 0)
        {
            if (head->val == 0)
            {
                head = new ListNode(input % 10);
                current = head;
            }
            else
            {
                current->next = new ListNode(input % 10);
                current = current->next;
            }
            //            cout <<"head: "<< head->val<< " current: "<< current->val << endl;
            input /= 10;
        }
        //        cout << head->val << endl;
        return head;
    }
    void printList(ListNode *head) const
    {
        while (head)
        {
            cout << head->val << " ";
            head = head->next;
        }
    }
};

using namespace std;

int main()
{
    Solution s;
    ListNode *n1 = new ListNode(0);
    ListNode *n2 = new ListNode(0);
    ListNode *n3 = new ListNode(2);
    n1->next = n2;
    n2->next = n3;
    ListNode *m1 = new ListNode(5);
    ListNode *m2 = new ListNode(5);
    ListNode *m3 = new ListNode(5);
    ListNode *m4 = new ListNode(5);
    m1->next = m2;
    m2->next = m3;
    m3->next = m4;
    //    ListNode* result  = s.expand(0);
    ListNode *result = s.addTwoNumbers(n1, m1);
    //    ListNode node = ListNode();
    //    s.printList(&node);
    //    ListNode* result = s.addTwoNumbers(&node, &node);
    s.printList(result);
    return 0;
}
