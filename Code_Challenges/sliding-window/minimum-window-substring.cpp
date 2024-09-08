// https://leetcode.com/problems/minimum-window-substring
// Minimum Window Substring (LeetCode #76)
#include <vector>
#include <unordered_map>
#include <string>
#include <limits.h>
using namespace std;

// solution 1: very slow
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> charCount;
        for (char c : t) {
            charCount[c]++;
        }

        unordered_map<char, int> windowCount;
        size_t minLength = s.size() + 1;
        int l = 0;
        int start = 0;

        for(size_t r = 0 ; r < s.size(); r++)
        {
            if(charCount.find(s[r]) != charCount.end())
            {
                windowCount[s[r]]++;
            }

            while (reached(charCount, windowCount))
            {
                if((r - l + 1) < minLength)
                {
                    minLength = r - l + 1;
                    start = l;
                }

                if(charCount.find(s[l]) != charCount.end())
                {
                    windowCount[s[l]]--;
                }
                l++;
            }
        }

        return minLength > s.size() ? "" : s.substr(start, minLength);
    }

    bool reached(unordered_map<char, int>& charCount, unordered_map<char, int>& windowCount) {
        for(auto& item : charCount) {
            char c = item.first;
            if(windowCount[c] < charCount[c])  
                return false;
        }
        return true;
    }
};

// solution 2: fast
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> charCount;
        for (char c : t) {
            charCount[c]++;
        }

        unordered_map<char, int> windowCount;
        int minLength = INT_MAX;
        int l = 0, start = 0;
        int required = charCount.size();  // Number of unique characters that need to be formed
        int formed = 0;  // Tracks how many unique characters in the current window have met the required count

        for (int r = 0; r < s.size(); r++) {
            char c = s[r];
            if (charCount.find(c) != charCount.end()) {
                windowCount[c]++;
                if (windowCount[c] == charCount[c]) {
                    formed++;  // One unique character is fully formed
                }
            }

            // Try to contract the window until it is no longer 'desirable'
            while (formed == required) {
                if (r - l + 1 < minLength) {
                    minLength = r - l + 1;
                    start = l;
                }

                char leftChar = s[l];
                if (charCount.find(leftChar) != charCount.end()) {
                    windowCount[leftChar]--;
                    if (windowCount[leftChar] < charCount[leftChar]) {
                        formed--;  // A unique character is no longer fully formed
                    }
                }
                l++;  // Shrink the window from the left
            }
        }

        return minLength == INT_MAX ? "" : s.substr(start, minLength);
    }
};
