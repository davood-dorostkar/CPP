// https://leetcode.com/problems/range-sum-query-immutable/
// Range Sum Query - Immutable (LeetCode #303)

#include <vector>
using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++ )
        {
            if (i == 0)
                sums.push_back(nums[i]);
            else
                sums.push_back(nums[i] + sums[i -1]);
                
        }
    }
    
    int sumRange(int left, int right) {
        if(left != 0)
        {
            return sums[right] - sums[left -1];
        }
        else
            return sums[right];

    }
private:
    vector<int> sums;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */