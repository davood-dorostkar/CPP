#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

pair<int, int> countVowelsConsonants(string str)
{
    char vowels[5] = {'a','e','o','i','u'};
    pair<int, int> freq;
    for(const char& c : str)
    {
        if(isalpha(c))
        {
            bool flag = false;
            for(auto v : vowels)
            {
                if(v==c)
                {
                    flag = true;
                    break;
                }
            }

            if(flag)
                freq.first++;
            else
                freq.second++;
        }
    }
    return freq;
}


void print(pair<int, int> freq)
{
    cout << "vowels: " << freq.first << endl;
    cout << "consonants: " << freq.second << endl;
}

int main()
{
   string str;
//   cin >> str;
   str = "12dsls slie 32 1sdd";
   print(countVowelsConsonants(str));
}
