// https://leetcode.com/problems/container-with-most-water/description/
// Container With Most Water (LeetCode #11)
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(const vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_area = 0;
        
        while (left < right) {
            // Precompute the heights and their difference to avoid repeated calculations
            int leftHeight = height[left];
            int rightHeight = height[right];
            int width = right - left;
            
            // Calculate the area based on the shorter height
            int current_area = (leftHeight < rightHeight ? leftHeight : rightHeight) * width;
            if (current_area > max_area) {
                max_area = current_area;
            }
            
            // Move the pointer corresponding to the shorter line inward
            // hint: a good example of why you should do this: [6,3,6,2,5,4,8,9,7]
            if (leftHeight < rightHeight) {
                ++left;
            } else {
                --right;
            }
        }
        
        return max_area;
    }
};