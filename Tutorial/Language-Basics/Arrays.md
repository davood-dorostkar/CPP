## Definition

keep in mind: arrays are statically allocated in the memory:

```cpp
int var[3] = {2, 4, 6};
```

find the distance between two items (in general for each data in memory):

> get the address of memory, then cast it to long (it is in OS default address type. in addition, if you print `&var`, it is in hex and not visually good)

```cpp
std::cout << (long)&var[2] - (long)&var[0] << std::endl;
```

## Multidimentional array
```cpp
int multiArray[row][col]
```

![](/images/m-dim-array.jpeg)

## Pass arrays to functions
there are 3 ways:
```cpp
void arrayAsPointer(int *array, int size)
{
    for(int i=0; i<size; i++)
        std::cout<<array[i]<<" ";
}
```
```cpp
void arraySized(int array[3], int size)
{
    for(int i=0; i<size; i++)
        std::cout<<array[i]<<" ";
}
```
```cpp
void arrayUnSized(int array[], int size)
{
    for(int i=0; i<size; i++)
        std::cout<<array[i]<<" ";
}
```
## Iterators for raw arrays
```cpp
#include <iterator>

int arr[10];

int* start = std:begin(arr);
int* end = std::end(arr);
```
## Fill an array with sequential values
```cpp
#include <numeric>

std::iota(startPtr, endPtr, startingValue);
```
using together with iterators:
```cpp
std::iota(std:begin(arr), std::end(arr), 5);
```
## std::array
STL array is more flexible and safer. for example `.at` checks availability before access to index:
```cpp
#include <array>

int arr[10];
arr[1000] = 8; // core dump

std::array<int, 10> stdarr;
stdarr.at(1000) = 8; // gives verbose error
```
## Dot product
```cpp
for(int i=0; i<row; i++)
{
    result[i]=0;
    for(int j=0; j<col; j++)
    {
      result[i]+=(matrix[i][j] * vector[j]);
    }
}
```
## Reverse an array

```cpp
void reverseArray(int arr[], int N){
    // Your code goes here
    for(int i = 0; i < N/2; i++){
        int temp = arr[i];
        arr[i] = arr[N-i-1];
        arr[N-i-1] = temp;
    }
}
```
## Sort an array

```cpp
for(int i=0; i<size; i++)
{
    for(int j=i; j>0; j--)
    {
        if(array[j]<array[j-1])
        {
            int temp = array[j-1];
            array[j-1]=array[j];
            array[j]=temp;
        }
        else break;
    }
}
```
