// https://leetcode.com/problems/find-the-duplicate-number/description/
// Find the Duplicate Number (LeetCode #287)
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

// solution 1
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int, int> list;
        for(auto& n : nums)
        {
            if(list.find(n) != list.end())
            {
                return n;
            }
            else
            {
                list[n]++;
            }
        }
        return 0;
    }
};

// solution 2: faster 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];

        // Phase 1: Find the intersection point in the cycle.
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find the entrance to the cycle (duplicate number).
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};