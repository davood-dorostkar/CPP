#include <iostream>
#include <string>
#include <vector>
using namespace std;

class VowelChecker
{
    vector<string> _vowels;
public:
    VowelChecker()
    {
        _vowels.push_back("a");
        _vowels.push_back("i");
        _vowels.push_back("o");
        _vowels.push_back("u");
        _vowels.push_back("e");
    }
    void print()
    {
        for(auto v : _vowels) cout << v << endl;
    }
    int count(string s)
    {
        int len = s.length();
        int count=0;
        for(int i=0; i < len; i++)
        {
            string currentString = s;
            for(auto v : _vowels)
            {
                if(currentString == v) count++;
                cout << "current: " << currentString << " v: " << v << endl;
            }

        }
        return count;
    }
};

int main()
{
    string input;
    getline(cin , input);
    cout << "checking ..." << endl;
    VowelChecker* checker = new VowelChecker;
//    cout << checker->count(&input);
//    checker->print();
    return 0;
}
