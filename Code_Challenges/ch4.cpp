#include <unordered_map>
#include <iostream>
#include <stack>

class Solution
{
public:
    std::unordered_map<char, int> open =
        {
            {'(', 1},
            {'{', 2},
            {'[', 3}};
    std::unordered_map<char, int> close =
        {
            {')', 1},
            {'}', 2},
            {']', 3}};
    std::stack<char> list;
    bool isValid(std::string s)
    {
        for (char &c : s)
        {
            if (open.count(c))
                list.push(c);
            else if (close.count(c))
            {
                if (list.empty())
                    return false;
                if (close[c] == open[list.top()])
                    list.pop();
                else
                    return false;
            }
            else
                return false;
        }
        if (list.empty())
            return true;
        return false;
    }
};

int main()
{
    std::string s1 = "({[]})";
    std::string s2 = "({[[}]";
    std::string s3 = "]({[[}]";
    Solution s;
    if (!s.isValid(s1) || s.isValid(s2) || s.isValid(s3))
        return -1;
    std::cout << "OK";
    return 0;
}