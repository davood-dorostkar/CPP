# const
## pass to function
it is a best practice to make sure the function will not change the variable value even inside the function scope. if the function changes the variable, you will get a compiler error.
```cpp
int doubleInput(const int input)
{
    // input++; // adding this will produce a compile error
    int h = input *2;
    return h;
}
```
## const after function
this means that the function is not allowed to alter the `this` object.

### Example
```cpp
struct X
{
    void foo() const // <== The implicit "this" pointer is const-qualified!
    {
        _x = 42; // ERROR! The "this" pointer is implicitly const
        _y = 42; // OK (_y is mutable)
    }

    void bar(X& obj) const // <== The implicit "this" pointer is const-qualified!
    {
        obj._x = 42; // OK! obj is a reference to non-const
        _x = 42; // ERROR! The "this" pointer is implicitly const
    }

    int _x;
    mutable int _y;
};
```
