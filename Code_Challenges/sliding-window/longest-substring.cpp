// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
// Longest Substring Without Repeating Characters (LeetCode #3)
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0)
            return 0;

        unordered_map<char, int> charsPos;
        int max_len = 1;
        charsPos[s[0]] = 0;
        int l = 0;
        int r = 1;

        while(r < s.size())
        {
            char letter = s[r];
            auto it = charsPos.find(letter);
            if (it != charsPos.end() && it->second >= l) 
            {
                l = it->second + 1;
            }

            charsPos[letter] = r;
            max_len = max(r - l + 1, max_len);
            r++;
        }
        return max_len;
    }
};