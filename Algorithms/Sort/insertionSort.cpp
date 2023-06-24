#include <iostream>
#include <array>
#include <vector>

using namespace std;

template <typename type>
void insertionSort(vector<type> &in)
{
    for (size_t i = 1; i < in.size(); ++i)
    {
        type target = in[i];
        size_t j;
        for (j = i; j > 0 && target < in[j - 1]; --j)
        {
            in[j] = in[j - 1];
        }
        in[j] = target;
    }
}

template <typename type>
void print(vector<type> const vec)
{
    for (type item : vec)
    {
        cout << item << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> vec = {1, 2, 32, 5, 23};
    insertionSort(vec);
    print(vec);
    vector<string> str = {"ss", "sd", "ar", "nm"};
    insertionSort(str);
    print(str);
    return 0;
}