with templates you can define a single function or class for different data types.
## Template function
### Define
```cpp
template <typename T>
T sumTwo(T in1, T in2)
{
    return in1+in2;
}
```
### Usage
```cpp
int a = 90;
int b = 1; 
std::cout << sumTwo(a,b);
```
### Multiple types
you can define multiple types in your template
#### syntax
```cpp
template <typename T, typename U, typename V>
T functionName (U  parameter1, V  parameter2,...)
{
    function statements;
}

```
#### Example
```cpp
T getBigger(T input1, U input2)
{
    if(input1 > input2)
        return input1;
    return input2;
}
```
## Template Class
### Syntax
```cpp
template<class T>
class Score
{
private:
        T scorenumber;
public:
       Score(T args){scorenumber = args;}
};
```
### Define
```cpp
template <class T>
class StudentRecord
{
        T grade;
        int studentId;
    public:
        StudentRecord(T input);
        void setId(int idIn);
};
```
> all member functions must be treated as generic, no matter they use template types or not, because the class containing them is a template. like:
```cpp
template<class T>
StudentRecord<T>::StudentRecord(T input)
{
    grade=input;
}
```
```cpp
template<class T>
void StudentRecord<T>::setId(int idIn)
{
    studentId = idIn;
}
```
### Usage
You should specify what data type you are using.
```cpp
Score<int> myscore(40);
```
### Issues with arrays
arrays in C++ are not objects, they are a block of contiguous memory that holds a collection of elements of the same type. This means that arrays cannot be passed by value to a function or a constructor, they can only be passed by reference or pointer.

When you try to use an array as a template parameter, the compiler treats the array as a pointer to the first element of the array. This can lead to unexpected behavior, as the size and type of the array are lost.
```cpp
template <typename T>
class MyTemplateClass {
public:
    MyTemplateClass(T array[]) {
        // constructor code here
    }
};
```
```cpp
int myArray[] = {1, 2, 3};
MyTemplateClass<int> myClass(myArray);
```
The array is treated as a pointer to the first element, so the constructor will only receive a pointer to the integer 1. The size and type information of the array is lost, which can lead to errors in the class.

To avoid this problem, it is recommended to use a std::array or std::vector instead of a raw array when working with template classes in C++. These containers provide a convenient and safe way to manage collections of data in a template class.

Another solution is to pass a default value to the constructor, so it can allocate memory to the whole array. like this:
```cpp
const int SIZE = 5;
template <class T>
class StudentRecord
{
    private:
        const int size = SIZE;
        T grades[SIZE];
    public:
        StudentRecord(T defaultInput);
};

template<class T>
StudentRecord<T>::StudentRecord(T defaultInput)
{
    for(int i=0; i<SIZE;++i)
    {
        grades[i] = defaultInput;
    }
}
```
## Non-type template
in this case you are telling the compiler you have an undefined variable (not a type) that should be defined in compile time. 
```cpp
template <typename type, size_t n>
void print(array<type, n> arr)
{
    for(type i=0; i< n; i++)
        cout << arr[i];
}
```
```cpp
int main()
{
    array<int,4> arr = {1,2,3,5};
    print<int, 4>(arr);
}
```
you can also set a default value for the non-type template parameter:
```cpp
template <size_t n=1>
```