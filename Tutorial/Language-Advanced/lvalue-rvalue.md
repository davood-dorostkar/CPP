# lvalues and rvalues

## L-values and R-values:
- **L-values** (locator values) have a specific memory location and can (typically) appear on the left side of an assignment. For example, in `int i = 10;`, `i` is an l-value.
- **R-values** are temporary values that do not have a specific memory location until they are assigned to an l-value. For example, `10` in the same expression is an r-value.

## L-value References and R-value References:
- **L-value references** can only bind to l-values. They allow the modification of the referenced value (use `&`).
- **R-value references** use double ampersands (`&&`) and can only bind to r-values, enabling optimizations like move semantics.

## Assignment
in `int i = 10;`, `i` is lvalue and `10` is rvalue, but in `int a = i;` both `a` and `i` are lvalue.

you can assign a value to a modifiable (non-const) lvalue, so this code is invalid:
```cpp
int GetValue()
{
    return 10;
}

int main()
{
    GetValue() = 5; // invalid
}
```
but this one is valid:
```cpp
int& GetValue()
{
    static int value = 10;
    return value;
}

int main()
{
    GetValue() = 5; // valid
}
```
## Functions Accepting lvalues and rvalues
- you can only accept lvalues:
```cpp
void SetValue(int& value)
{
    //
}

int main()
{
    int i = 10;
    SetValue(i); // valid
    SetValue(10); // invalid
}
```
- you can only accept rvalues:
```cpp
void SetValue(int&& value)
{
    //
}

int main()
{
    int i = 10;
    SetValue(i); // invalid
    SetValue(10); // valid
}
```
- accept both lvalue and rvalue:
```cpp
void SetValue(int value)
{
    //
}
```
or 
```cpp
void SetValue(const int& value)
{
    //
}
```
### Example
```cpp
void PrintName(std::string& name)
{
    std::cout << name << std::endl;
}

int main()
{
    std::string firstName = "Davood";
    std::string lastName = "Dorostkar";
    std::string fullName = firstName + lastName;

    PrintName(fullName); // valid
    PrintName(firstName + lastName); // invalid
}
```

## Function Overloading Benefits:
- Functions can be overloaded to accept either l-values or r-values by defining versions that take l-value references or r-value references, respectively.
- assume the function takes a `const T& param` input, meaning it is compatible with both rvalues and lvalues, if there is also an overloaded function with rvalue input like `T&& param`, the latter will be chosen by the compiler.

```cpp
void PrintName(const std::string& name)
{
    std::cout << "[lvalue]:"<< name << std::endl;
}

void PrintName(std::string&& name)
{
    std::cout << "[rvalue]:"<< name << std::endl;
}

int main()
{
    std::string firstName = "Davood";
    std::string lastName = "Dorostkar";
    std::string fullName = firstName + lastName;

    PrintName(fullName); // valid; first definition runs
    PrintName(firstName + lastName); // valid; second definition runs
}
```
- it is a powerful way to detect the temporary values (rvalues), and do something special to them, like optimization.
- it is very usefull especially with [Move Semantics](/Tutorial/Modern/move.md). if we know that we're taking in a temporary object then we don't have to worry about making sure that we keep it alive and keep it intact and copy it. we can simply steal the resources that might be attached to that specific object and use them somewhere else because we know that it's temporary; it's not going to exist for very long. 
  
  whereas if you take in something like `const int& param` then (apart from the fact that it's cost) you can't really steal anything from that `param` because it might be used in a number of functions whereas `T&& param` is clearly something that is temporary only going to be used with this particular call of function (remember the input `firstName + lastName`) and that's where the power really comes from.