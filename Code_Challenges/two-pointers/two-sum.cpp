// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted
// Two Sum II - Input Array is Sorted (LeetCode #167)
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size() - 1;

        // Pre-check boundaries
        if (numbers[i] + numbers[i + 1] > target || numbers[j] + numbers[j - 1] < target) {
            return {}; // No solution possible with given input
        }
        
        while (i < j) {
            int sum = numbers[i] + numbers[j];
            if (sum == target) {
                return {i + 1, j + 1};  // Return early
            } else if (sum < target) {
                i++;
            } else {
                j--;
            }
        }
        return {}; 
    }
};
