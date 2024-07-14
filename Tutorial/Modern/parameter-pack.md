# Parameter Pack

## Definition

A parameter pack is a template parameter that can accept zero or more template arguments. This feature was introduced in C++11 and is particularly useful for creating variadic templates, which are templates that can take a variable number of arguments.

## Usage

Parameter packs can be used in both template parameter lists and function parameter lists. They are indicated by an ellipsis (`...`) following the parameter name.

## Template Parameter Packs

```cpp
template<typename... Ts>
class MyClass {
    // ...
};
```

In this example, `Ts` is a template parameter pack that can hold an arbitrary number of types.

## Function Parameter Packs

```cpp
template<typename... Ts>
void myFunction(Ts... args) {
    // ...
}
```

Here, `Ts` is a template parameter pack, and `args` is a function parameter pack that can hold an arbitrary number of function arguments.

## Expansion of Parameter Packs

Parameter packs can be expanded using the ellipsis (`...`). This is typically done in contexts like function calls, initialization lists, or other places where multiple arguments are needed.

```cpp
template<typename... Ts>
void printAll(Ts... args) {
    (std::cout << ... << args) << '\n';
}
```

In this example, the parameter pack `args` is expanded in the expression `(std::cout << ... << args)`, which prints all the arguments to `std::cout`.

## Using each parameter 

### Method 1: Using a Fold Expression (Modern C++)

Fold expressions are a convenient way to handle parameter packs, introduced in C++17. You can use them not just for simple operations like printing, but also for more complex operations if needed.

### Example: Using Each Parameter Separately

```cpp
#include <iostream>

// Function template that processes each argument separately
template<typename... Args>
void processAll(Args&&... args) {
    // Lambda that processes each argument
    auto process = [](const auto& arg) {
        std::cout << "Processing: " << arg << '\n';
    };
    
    // Expand the parameter pack using fold expression with the comma operator
    (process(args), ...);
}

int main() {
    // Call the function with multiple parameters
    processAll(1, 2.5, "Hello", std::string("world"));
    return 0;
}
```

### Explanation

1. **Lambda Function**: `auto process = [](const auto& arg)` defines a lambda that processes each argument. In this case, it simply prints the argument.
2. **Fold Expression**: `(process(args), ...)` expands the parameter pack, calling the lambda for each argument. The comma operator is used here to execute the lambda for each argument in the pack.

### Method 2: Using `std::initializer_list` (Older C++)

Before C++17, you could use `std::initializer_list` to achieve a similar effect.

```cpp
#include <iostream>

// Function template that processes each argument separately
template<typename... Args>
void processAll(Args&&... args) {
    // Initialize an initializer_list to expand the parameter pack
    std::initializer_list<int>{(std::cout << "Processing: " << args << '\n', 0)...};
}

int main() {
    // Call the function with multiple parameters
    processAll(1, 2.5, "Hello", std::string("world"));
    return 0;
}
```

### Explanation

1. **`std::initializer_list`**: This is used to expand the parameter pack. Each element in the list is the result of the expression `(std::cout << "Processing: " << args << '\n', 0)`, where `0` is just a placeholder to match the type requirements of `std::initializer_list<int>`.

### Method 3: Using Recursion

You can also use recursion to handle each parameter separately, though this is less efficient and more verbose.

```cpp
#include <iostream>

// Base case: no arguments
void processAll() {}

// Recursive case: process the first argument and then recurse
template<typename T, typename... Args>
void processAll(T&& first, Args&&... rest) {
    std::cout << "Processing: " << first << '\n';
    processAll(std::forward<Args>(rest)...);
}

int main() {
    // Call the function with multiple parameters
    processAll(1, 2.5, "Hello", std::string("world"));
    return 0;
}
```

### Explanation

1. **Base Case**: The base case `void processAll()` handles the termination of recursion when no arguments are left.
2. **Recursive Case**: `template<typename T, typename... Args> void processAll(T&& first, Args&&... rest)` processes the first argument and then calls itself with the rest of the arguments.
