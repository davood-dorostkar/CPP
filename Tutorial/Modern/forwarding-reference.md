# Forwarding References

## Definition

A forwarding reference, also known as a universal reference, is a special type of reference that can bind to both lvalues and rvalues. It is used in template code to enable perfect forwarding, which ensures that the value category (lvalue or rvalue) and the const-volatile qualification of arguments are preserved when they are passed to another function.

## Syntax

A forwarding reference is declared using `T&&` where `T` is a template parameter that is deduced.

```cpp
template<typename T>
void myFunction(T&& arg) {
    // ...
}
```

Here, `T&&` is a forwarding reference.

## Perfect Forwarding

Perfect forwarding is the practice of forwarding arguments to another function while preserving their value category. This is achieved using `std::forward`.

```cpp
template<typename T>
void wrapper(T&& arg) {
    // Forward the argument to another function
    actualFunction(std::forward<T>(arg));
}
```

- **`std::forward<T>(arg)`**: This function casts `arg` back to its original type, preserving its value category (lvalue or rvalue).

## Relation to Template

In the context of perfect forwarding and forwarding references, it is mandatory to use template types to achieve the desired flexibility and correctness. The primary purpose of forwarding references (also known as universal references) is to enable perfect forwarding, where the type and value category of arguments (lvalue or rvalue) are preserved when they are passed to another function. This requires the use of template parameters.

### Template Types for Forwarding References

Here's why template types are necessary for forwarding references:

1. **Type Deduction**: Template parameters allow the compiler to deduce the exact type and value category of the arguments being passed.
2. **Perfect Forwarding**: `std::forward` requires template parameters to cast the arguments back to their original type and value category.

#### Example with Template Parameter (Perfect Forwarding)

```cpp
#include <iostream>
#include <utility> // For std::forward

// Template function to demonstrate perfect forwarding
template<typename T>
void wrapper(T&& arg) {
    // Forward the argument to another function
    process(std::forward<T>(arg));
}

void process(int& arg) {
    std::cout << "Lvalue reference: " << arg << std::endl;
}

void process(int&& arg) {
    std::cout << "Rvalue reference: " << arg << std::endl;
}

int main() {
    int a = 42;
    wrapper(a); // Calls process(int&)
    wrapper(42); // Calls process(int&&)
    return 0;
}
```

In this example:
- `wrapper` is a template function that accepts a forwarding reference (`T&& arg`).
- `std::forward<T>(arg)` ensures that the argument is forwarded with its original value category preserved.