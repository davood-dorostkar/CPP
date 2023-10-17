#include <iostream>
#include <unordered_map>
using namespace std;

// USING REFERENCES IN ARGUMENT AND LOOPS TO
// PREVENT UNNECESSARY COPY ADN IMPROVE PERFORMANCE

void repeated(const string &str)
{
    unordered_map<char, int> num;
    for(const char &c : str)
        if(c!=' ') num[c]++;
    for(const char &c : str)
        if(num[c]==1)
        {
            cout << c << endl;
            return;
        }
}

int main()
{
    string str = "davood dorostkar";
    repeated(str);
    return 0;
}
