// https://leetcode.com/problems/3sum/description/
// 3Sum (LeetCode #15)
#include <vector>
#include <algorithm>
using namespace std;


// solution 1: brute force O(n^3)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.size()<3)
            return {{}};
        vector<vector<int>> result;
        vector<int> triplet;
        for(int i = 0; i < nums.size() - 2; i++)
        {
            for(int j = i+1; j < nums.size() - 1; j++)
            {
                for(int k = j+1; k < nums.size(); k++)
                {
                    if(nums[i]+nums[j]+nums[k] == 0)
                    {
                        triplet = {nums[i], nums[j], nums[k]};
                        sort(triplet.begin(), triplet.end());
                        if(find(result.begin(), result.end(), triplet) == result.end())
                            result.push_back(triplet);
                    }
                        
                }
            }
        }
        return result;
    }
};

// solution 2
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        
        if(nums.size() < 3)
            return result;

        sort(nums.begin(), nums.end());

        for(int i = 0; i < nums.size() - 2; i++) {
            // Skip duplicates 
            if(i > 0 && nums[i] == nums[i-1])
                continue;

            int j = i + 1;
            int k = nums.size() - 1;

            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                
                if(sum == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                    j++;
                    k--;

                    // Skip duplicates 
                    while(j < k && nums[j] == nums[j-1])
                        j++;
                    while(j < k && nums[k] == nums[k+1])
                        k--;
                }
                else if(sum < 0) {
                    j++;
                } else {
                    k--;
                }
            }
        }
        return result;
    }
};
