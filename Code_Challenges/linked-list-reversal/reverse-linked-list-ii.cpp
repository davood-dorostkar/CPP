// https://leetcode.com/problems/reverse-linked-list-ii/
// Reverse Linked List II (LeetCode #92)

#include <iostream>
#include <vector>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
   ListNode* reverseBetween(ListNode* head, int left, int right) {
       ListNode* dummy = new ListNode();
       dummy->next = head;
       ListNode* pre = dummy;

       for(int i = 0; i < left-1; i++)
           pre = pre->next;

       ListNode* curr = pre->next;
       for(int i = 0; i < right-left; i++)
       {
           ListNode* forw = curr->next;
           curr->next = forw->next;
           forw->next = pre->next;
           pre->next = forw;
       }
       return head;
   }
};


ListNode* makeList(vector<int> in)
{
    ListNode* pre = new ListNode(0);
    ListNode* head;
    for(int i = 0; i < in.size(); i++)
    {
        ListNode* node = new ListNode(in[i]);
        if(i==0) head = node;
        pre->next = node;
        pre = node;
    }
    return head;
}

void printList(ListNode* head)
{
    cout << "list: ";
    while(head != nullptr)
    {
        if(head->next != nullptr)
            cout << head->val << ", ";
        else
            cout << head->val << endl;
        head = head->next;
    }
}

int main() {
    vector<int> vec = {1,2,3,4,5};
    ListNode* head = makeList(vec);
    printList(head);
    Solution s;
    ListNode* update = s.reverseBetween(head, 2,4);
    printList(update);

    return 0;
}
