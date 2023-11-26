#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> numMap;
        for (int i = 0; i < nums.size(); ++i)
        {
            int complement = target - nums[i];
            if (numMap.find(complement) != numMap.end())
            {
                return {numMap[complement], i};
            }
            numMap[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    Solution s;
    vector<int> vec = {3, 1, 2, 3};
    vector<int> res = s.twoSum(vec, 6);
    for (int i : res)
    {
        cout << i << endl;
    }
}