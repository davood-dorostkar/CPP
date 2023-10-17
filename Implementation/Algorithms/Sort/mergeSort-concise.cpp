#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int> &vec)
{
    for (auto item : vec)
    {
        cout << item << " ";
    }
}

void merge(vector<int> &vec, vector<int> &left, vector<int> &right)
{
    int leftPos = 0;
    int rightPos = 0;
    int pos = 0;
    while (leftPos < left.size() && rightPos < right.size())
    {
        if (left[leftPos] < right[rightPos])
            vec[pos++] = left[leftPos++];
        else
            vec[pos++] = right[rightPos++];
    }

    while (leftPos < left.size())
        vec[pos++] = left[leftPos++];

    while (rightPos < right.size())
        vec[pos++] = right[rightPos++];
}

void mergeSort(vector<int> &vec)
{
    if (vec.size() < 2)
        return;
    vector<int> left, right;
    for (int i = 0; i < vec.size() / 2; i++)
        left.push_back(vec[i]);
    for (int i = vec.size() / 2; i < vec.size(); i++)
        right.push_back(vec[i]);

    mergeSort(left);
    mergeSort(right);
    merge(vec, left, right);
}

int main()
{

    vector<int> test = {5, 6, 1, 7, 3, 9, 6, 8, 12, 32, 1, 54, 6, 8, 9, 3, 5, 7, 9, 90};
    mergeSort(test);
    print(test);
    return 0;
}
