#include <iostream>
#include <array>
#include <vector>
using namespace std;

template <typename type>
void print(vector<type> const vec)
{
    for (type item : vec)
        cout << item << " ";
    cout << endl;
}

template <typename type>
void quickSort(vector<type> &vec)
{
    if (vec.size() < 2)
        return;
    vector<type> smaller, greater;
    type pivot = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] <= pivot)
            smaller.push_back(vec[i]);
        else
            greater.push_back(vec[i]);
    }

    quickSort(smaller);
    quickSort(greater);

    vec.clear();
    vec.insert(vec.begin(), smaller.begin(), smaller.end());
    vec.push_back(pivot);
    vec.insert(vec.end(), greater.begin(), greater.end());
}

int main()
{
    vector<int> vec = {1, 4, 34, 2, 56, 12, 2};
    quickSort(vec);
    print(vec);
    return 0;
}
