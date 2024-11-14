// https://leetcode.com/problems/reverse-linked-list/
// Reverse Linked List (LeetCode #206)

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
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
    ListNode* reverseList(ListNode* head) {
        ListNode* newNext = nullptr;
        while(head != nullptr)
        {
            ListNode* temp = head->next;
            head->next = newNext;
            newNext = head;
            head = temp;
        }
        return newNext;
    }
};