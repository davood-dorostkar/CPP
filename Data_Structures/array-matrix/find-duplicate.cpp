#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template <size_t n>
vector<int> findDuplicate(const array<int, n> &arr)
{
    vector<int> duplicates;
    unordered_map<int, int> freq;
    for(const int& i : arr)
        freq[i]++;
    for(const pair<int,int>& pair : freq)
        if(freq[pair.second]>1) duplicates.push_back(pair.first);
    return duplicates;
}

template <typename type>
void print(const vector<type> &vec)
{
    for(const type &i : vec)
        cout << i << " ";
}

int main()
{
    array<int,7> arr = {1,2,3,5,3,2,7};
    print(findDuplicate(arr));
    return 0;
}
