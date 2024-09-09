// https://leetcode.com/problems/linked-list-cycle/description/
// Linked List Cycle (LeetCode #141)
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

// note:
// the two pointers method can be suboptimal in some cases.
// in fact the fast ptr might go back to a point that the slow ptr
// has already passed. so it must chase slow.
// in this case, the loop is identified in the 3rd time the fast ptr
// loops the structure!
//          ListNode node1(1);
//          ListNode node2(2);
//          ListNode node3(3);
//          ListNode node4(4);
//          node1.next = &node2;
//          node2.next = &node3;
//          node3.next = &node4;
//          node4.next = &node1;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
 
// solution 1: slow
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL || head->next == NULL)
            return false;
            
        unordered_set<ListNode*> past;
        while(head->next != NULL)
        {
            if(past.find(head->next) != past.end())
                return true;
            else
            {
                past.insert(head);
                head = head->next;
            }
        }
        return false;        
    }
};

// solution 2: faster
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL || head->next == NULL)
            return false;

        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next)
        {

            slow = slow->next;
            fast = fast->next->next;

            if(fast == slow)
                return true;
        }
        return false;        
    }
};

// solution 3: fastest (with minor changes)
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next)
            return false;

        ListNode* slow = head;
        ListNode* fast = head->next; 

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }
        return false;
    }
};
