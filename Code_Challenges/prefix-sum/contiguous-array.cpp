// https://leetcode.com/problems/contiguous-array
// Contiguous Array (LeetCode #525)

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> sumIndexMap;
        int maxLength = 0;
        int cumulativeSum = 0;

        // Initialize the map with sum 0 at index -1
        sumIndexMap[0] = -1;

        for (size_t i = 0; i < nums.size(); i++) {
            cumulativeSum += (nums[i] == 0) ? -1 : 1;
            // If the cumulative sum has been seen before, a balanced subarray is found
            if (sumIndexMap.find(cumulativeSum) != sumIndexMap.end()) {
                int subarrayLength = i - sumIndexMap[cumulativeSum];
                maxLength = max(maxLength, subarrayLength);
            } else {
                // Store the first occurrence of this cumulative sum
                sumIndexMap[cumulativeSum] = i;
            }
        }

        return maxLength;
    }
};

/*
help: it is somehow tricky. 
important note is that if the cumulative sum reaches a point that it has been previously, 
the part between is a balanced subarray.
*/