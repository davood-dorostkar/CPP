#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<pair<int,int>> findPairs(const vector<int>& vec, int sum)
{
    vector<pair<int,int>> result;
    unordered_map<int, int> freq;
    for(const int& i : vec)
        ++freq[i];
    for(const auto& [i,f] : freq)
    {
        int expect = sum - i;
        if(freq[expect]>0)
        {
            result.push_back(make_pair(i,expect));
            --freq[i];
            --freq[expect];
        }
    }
    return result;
}

void print(vector<pair<int,int>> vec)
{
    for(auto v : vec)
        cout << v.first << ", " << v.second << endl;
}

int main()
{
    vector<int> vec = {1,2,4,3,8,9,11,13};
    vector<pair<int,int>> pairs = findPairs(vec,20);
    print(pairs);
    return 0;
}
