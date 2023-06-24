#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

void IsAnagrams(string str1, string str2)
{
    unordered_map<char, int> freq1;
    unordered_map<char, int> freq2;
    for(char c : str1)
    {
        if(c!=' ') freq1[c]++;
    }

    for(char c : str2)
    {
        if(c!=' ') freq2[c]++;
    }

    for(auto item : freq1)
    {
        if(freq2[item.first]==item.second) continue;
        else
        {
            cout << "not anagrams!" << endl;
            return;
        }
    }
    cout << "are anagrams" << endl;
}

int main()
{
    string str1;
    cout << "type first word" << endl;
    cin >> str1;
    string str2;
    cout << "type second word" << endl;
    cin >> str2;
    IsAnagrams(str1, str2);
    return 0;
}
