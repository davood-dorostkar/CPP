#include <iostream>
#include <vector>

using namespace std;

template <typename type>
void sort(vector<type> &input)
{
    vector<type> temp = input;
    vector<type> result;
    for (uint8_t i = 0; i < input.size(); i++)
    {
        type max = 0;
        size_t it_max;
        for (size_t it = 0; it < temp.size(); ++it)
        {
            if (temp[it] > max)
            {
                max = temp[it];
                it_max = it;
            }
        }
        input[i] = max;
        temp.erase(temp.begin() + it_max);
    }
}

template <typename type>
void print(vector<type> in)
{
    for (typename vector<type>::size_type i = 0; i < in.size(); i++)
    {
        cout << in[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr = {1, 43, 2, 4, 56};
    sort(arr);
    print(arr);
    return 0;
}
