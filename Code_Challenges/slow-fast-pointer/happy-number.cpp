// https://leetcode.com/problems/happy-number/description/
// Happy Number (LeetCode #202)
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        unordered_map<int, int> history;
        while(history.find(n) == history.end())
        {
            history[n]++;
            n = calcDigits(n);
            if(n == 1) return true;
        }
        return false;
    }

    int calcDigits(int n)
    {
        if(n < 10)
            return n * n;
        else
        {
            return (n % 10) * (n % 10) + calcDigits(n/10);
        }
    }
};