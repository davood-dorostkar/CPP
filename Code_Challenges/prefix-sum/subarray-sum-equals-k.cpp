// https://leetcode.com/problems/subarray-sum-equals-k/
// Subarray Sum Equals K (LeetCode #560)
#include <vector>
#include <unordered_map>
using namespace std;


// solution 1: brute force O(n^2)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        result = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            sub = 0;
            for(int j = i; j < nums.size(); j++)
            {
                sub += nums[j];
                if( sub == k)
                    result ++;
            }
        }
        return result;
    }
private:
    int sub;
    int result;
};

// solution 2: O(n)
class Solution {
public:
    int subarraySum(vector<int>& arr, int k) {
        int n = arr.size();
        makeSub(arr);

        unordered_map<int,int> mp;
        int ans = 0;

        for(int i = 0; i < n; i++)
        {
            if(prefix[i] == k) // the sum to this point is itself an answer
            {
                ans++;
            }

            if(mp.find(prefix[i] - k) != mp.end()) // there is a complement
            {
                ans += mp[prefix[i] - k]; // the complement itself may has been involved in multiple mixes
            }

            mp[prefix[i]]++;
        }

        return ans;
    }
    void makeSub(vector<int>& nums) {
        prefix.clear();
        for (int i = 0; i < nums.size(); i++) {
            int sum = (i == 0) ? nums[i] : nums[i] + prefix[i - 1];
            prefix.push_back(sum);
        }
    }

private:
    vector<int> prefix;
    int result;
};