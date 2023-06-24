#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>

using namespace std;

template <size_t n>
int findMissing(array<int, n> arr, int len)
{

    int expected = len * (len + 1)/2;
    int actual=0;
    for(size_t i=0; i< n; ++i)
    {
        actual += arr[i];
    }

    return  expected - actual;
}

int main()
{
    array<int,4> arr = {1,2,3,5};
    cout << findMissing(arr,5);

}
