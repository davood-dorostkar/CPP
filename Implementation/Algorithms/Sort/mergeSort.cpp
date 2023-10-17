#include <iostream>
#include <array>
#include <vector>
using namespace std;

template <typename type>
void print(vector<type> const vec)
{
    for (type item : vec)
    {
        cout << item << " ";
    }
    cout << endl;
}

template <typename type>
void merge(vector<type> &vec, vector<type> &tmp, size_t leftStart, size_t rightEnd)
{
    size_t leftEnd = (leftStart + rightEnd) / 2;
    size_t rightPos = leftEnd + 1;
    size_t leftPos = leftStart;
    size_t tmpPos = leftPos;

    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if (vec[leftPos] <= vec[rightPos])
            tmp[tmpPos++] = vec[leftPos++];
        else
            tmp[tmpPos++] = vec[rightPos++];
    }

    while (leftPos <= leftEnd)
        tmp[tmpPos++] = vec[leftPos++];
    while (rightPos <= rightEnd)
        tmp[tmpPos++] = vec[rightPos++];

    for (size_t i = leftStart; i <= rightEnd; i++)
        vec[i] = tmp[i];
}

template <typename type>
void mergeSort(vector<type> &vec, vector<type> &tmp, size_t leftStart, size_t rightEnd)
{
    if (leftStart < rightEnd)
    {
        size_t center = (leftStart + rightEnd) / 2;
        mergeSort(vec, tmp, leftStart, center);
        mergeSort(vec, tmp, center + 1, rightEnd);
        merge(vec, tmp, leftStart, rightEnd);
    }
}

template <typename type>
void mergeSort(vector<type> &vec)
{
    vector<type> tmp(vec.size());
    mergeSort(vec, tmp, 0, vec.size() - 1);
}

int main()
{
    vector<int> vec = {1, 4, 34, 2, 56, 12, 2};
    mergeSort(vec);
    print(vec);
    return 0;
}
