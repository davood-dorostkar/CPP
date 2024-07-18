# Function Pointers

## Introduction
- Function pointers allow assigning functions to variables.
- They enable passing functions as parameters to other functions.
- Function pointers enable passing different functions to a generic iterator function for varied behavior.

## Syntax and Usage:
- Typically written with an asterisk (*) and parentheses to denote a function type, e.g., `void (*function)()`.
```cpp
void HelloWorld()
{
    std::cout << "hello world!\n";
}

auto func = HelloWorld;
func();
```
```cpp
int Age(std::string name)
{
    std::cout << name << "'s age is 30\n";
    return 30;
}

auto ageFunc = Age;
ageFunc("Davood");
```
- you can also use function pointers with `&` like this. the result is the same:
```cpp
auto func = &HelloWorld;
```
## C-Style Function pointer
under the hood, the function pointer syntax is like this:
```cpp
void(*func)() = HelloWorld;
```
or in general:
```cpp
FUNCTION_OUTPUT(*F_PTR_NAME)(INPUTS);
``` 

## Advanced Syntax using typedef
Using `typedef` you can create a more readable alias for function pointer types.
```cpp
typedef void(*fptr)();
fptr func = HelloWorld;
func();
```
## Practical Example
```cpp
#include <iostream>
#include <vector>

void PrintValue(int value)
{
    std::cout << "value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int))
{
    for(auto value : values)
        func(value);
}

int main()
{
    std::vector<int> vector = {1, 3, 6, 2, 10};
    ForEach(vector, PrintValue);

    return 0;
}
```

## Simplified with Lambdas
  - [lambdas](/Tutorial/Modern/lambda.md) are more concise and flexible way to define inline anonymous functions that has no definition but declared inside the code.
  - Lambdas are preferred for their readability and ease of use compared to traditional function pointers.
```cpp
#include <iostream>
#include <string>
#include <vector>

void ForEach(const std::vector<int>& values, void(*func)(int))
{
    for(auto value : values)
        func(value);
}

int main()
{
    std::vector<int> vector = {1, 3, 6, 2, 10};
    ForEach(vector, [](int value){ std::cout << "value: " << value << std::endl; });

    return 0;
}
```