#include <iostream>
#include <array>
#include <vector>

using namespace std;

array<int,5> sort(array<int,5> input)
{
    vector<int> temp;
    array<int,5> result;
    for (uint8_t i=0; i<5; i++)
    {
        temp.push_back(input[i]);
    }

    for (uint8_t i =0;i< 5; i++)
    {
        int max=0;
        vector<int>::iterator it, it_max;
        for (it=temp.begin();it!=temp.end();it++)
        {
            if(*it>max)
            {
                max= *it;
                it_max = it;
            }
        }
        result[i] = max;
        temp.erase(it_max);
    }
    return result;
}


int main()
{
    array<int,5> arr = {1,43,2,4,56};
    array<int, 5> newArr = sort(arr);
    for (uint8_t i =0; i< 5; i++)
    {
        cout << newArr[i] << " ";
    }

    return 0;
}
