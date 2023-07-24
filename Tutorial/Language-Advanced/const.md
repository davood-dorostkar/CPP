### passing const to functions
it is a best practice to make sure the function will not change the variable value even inside the function scope. if the function changes the variable, you will get a compiler error.
```cpp
int doubleInput(const int input)
{
    // input++; // adding this will produce a compile error
    int h = input *2;
    return h;
}
```