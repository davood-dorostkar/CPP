// https://leetcode.com/problems/maximum-average-subarray-i/description/
// Maximum Average Subarray I (LeetCode #643)
#include <vector>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int window_sum = 0;
        
        for(int i = 0; i < k; ++i)
        {
            window_sum += nums[i];
        }
        int max_sum = window_sum;
        for(int i = k; i < nums.size(); ++i)
        {
            int right = nums[i];
            int left = nums[i - k];
            window_sum += (right - left);
            max_sum = (max_sum < window_sum) ? window_sum : max_sum;
        }

        return double(max_sum)/k;
    }
};