# Lambda Function

## Explanation of the Lambda Function

A lambda function in C++ is an anonymous function that can be defined inline and used where a function object or a [function pointer](/Tutorial/Language-Advanced/func-pointer.md) is required. whenever you have a function pointer you can use a lambda in C++ .

```cpp
[](int value){ std::cout << "value: " << value << std::endl; }
```
## Main Components 

1. **Capture List `[]`**:
   - This part allows the lambda function to capture variables from the surrounding scope. In this case, `laneID` is captured by value.


2. **Parameter List `()`**:
   - This specifies the parameters that the lambda function takes, just like in a regular function.
   - In this example, the lambda takes a single parameter `lane` of type `const Lane &`.

3. **Function Body `{}`**:
   - This is the actual code that the lambda function executes when called.

## Example 

Here’s another simple example to reinforce the syntax:

```cpp
auto add = [](int a, int b) { return a + b; };
```

## Quick Syntax Reference 

```cpp
[ capture_list ] ( parameter_list ) -> return_type { function_body }
```

- **Capture List**: `[&, x, &y]`
  - `[]` - No capture.
  - `[x, &y]` - Captures `x` by value, `y` by reference.
  - `[=]` - Captures all local variables by value.
  - `[&]` - Captures all local variables by reference.
  
- **Parameter List**: `(int a, int b)`
  - Defines the input parameters like a regular function.

- **Return Type (Optional)**: `-> int`
  - Specifies the return type explicitly if needed. Often deduced automatically.

- **Function Body**: `{ return a + b; }`
  - Contains the logic to execute.
- **mutable**:
  - you can change the values inside the lambda body that are captured with `mutable`; otherwise you are not allowed.
  ```cpp
  auto add = [a]() mutable { a = 5; };    
  ```
## vs Raw Function Pointers
if you want to capture something to the lambda, you cannot declare it as a raw function pointer like `void(*func)()` for example as a parameter to a function. instead you need to use `std::function` which is defined in `funcitonal` header like this:

```cpp
#include <iostream>
#include <vector>
#include <functional>

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
    for(auto value : values)
        func(value);
}

int main()
{
    std::vector<int> vector = {1, 3, 6, 2, 10};
    auto lambda = [](int value){ std::cout << "value: " << value << std::endl; };
    ForEach(vector, lambda);

    return 0;
}
```

## How It Works in `std::find_if`
`std::find_if` is a function from the `algorithm` library that searches through a container, like a vector, to find the first element that meets a specified condition.

- `std::find_if` takes a range and a predicate (the lambda function).
- It iterates over the elements in the range and applies the predicate to each element.
- The iteration stops when the predicate returns `true`, and `std::find_if` returns an iterator to that element. If no such element is found, it returns `vector.end()` iterator (this iterator is one place ahead of the last item in the memory which is an undefined value): more info in [vector](/Tutorial/DS-STL/Vector.md#understanding-stdvectorend)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> vector = {1, 3, 6, 2, 10};
    auto it  = std::find_if(vector.begin(), vector.end(), [](int value){ return value > 3;});
    std::cout << *it << std::endl;

    return 0;
}

```