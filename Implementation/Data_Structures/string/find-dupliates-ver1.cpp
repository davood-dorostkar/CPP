#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

vector<char> findDuplicate(string input)
{
    unordered_map<char, int> freq;
    vector<char> dpl;

    for(char c : input)
    {
        if(c!=' ')
        {
            freq[c]++;
        }
    }

    for(pair<char,int> c : freq)
    {
        if(c.second>1)
            dpl.push_back(c.first);
    }

    return dpl;
}

int main()
{
    string str;
    cout << "write a text" << endl;
    getline(cin, str);
    cout << "string: "<<str << endl;
    vector<char> duplicate = findDuplicate(str);
    cout << "duplicate: ";
    for(auto item : duplicate)
        cout << item << " ";
    return 0;
}
