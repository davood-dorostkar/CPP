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
## Multidimentional array
```cpp
int multiArray[row][col]
```
![](https://github.com/davood-dorostkar/CPP/blob/main/images/m-dim-array.jpeg)
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