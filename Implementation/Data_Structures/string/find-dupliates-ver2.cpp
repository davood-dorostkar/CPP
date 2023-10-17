#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<char> findDuplicate(string str)
{
    vector<char> dpl;
    unordered_map<char, int> num;
    for(const char& c : str)
    {
        if(c!=' ') num[c]++;
    }

    for(auto item : num)
        if(item.second>1) dpl.push_back(item.first);

    return dpl;

}

template <typename type>
void print(vector<type> vec)
{
    for(type i : vec) cout << i << " " << endl;
}

int main()
{
   string str;
//   cin >> str;
   str = "12dsls slie 32 1sdd";
   vector<char> result = findDuplicate(str);
   print(result);
}
