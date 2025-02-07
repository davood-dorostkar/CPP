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

## Forwarding References vs. Rvalue References in C++

**forwarding references** and **rvalue references** are concepts that are closely related but serve different purposes, especially when dealing with **perfect forwarding** in templates.



### 1. Rvalue References (`T&&`)
- **Introduced in C++11**, rvalue references allow you to distinguish between **lvalues** (variables that can be modified) and **rvalues** (temporary values or objects).
- **Rvalue reference** is declared using `T&&`, and it **binds** to **rvalues** (temporary objects) and allows **move semantics**.

### 2. Forwarding References (`T&&` in Templates)
- **Forwarding references** (also known as **universal references**) are a special case of rvalue references used in **templates**.
- They are **declared in template functions** and allow perfect forwarding of both **lvalues and rvalues**.

### How are Forwarding References Different?
- **Forwarding references** can bind to both **lvalues** and **rvalues**. 
- The **type deduction** in templates makes it possible to **forward the argument exactly as it was received**, without losing information about whether it was an lvalue or an rvalue.


### Key Differences Between Rvalue References and Forwarding References

| **Feature**               | **Rvalue Reference (`T&&`)**               | **Forwarding Reference (`T&&` in Templates)**      |
|---------------------------|--------------------------------------------|-----------------------------------------------------|
| **Binding**               | Binds to rvalues (temporary objects).      | Can bind to both lvalues and rvalues.               |
| **Purpose**               | Used to implement **move semantics**.      | Used to implement **perfect forwarding** in templates.|
| **Usage**                 | For functions that take **rvalues**.       | In template functions to **forward arguments** without losing their value category. |
| **Type Deduction**        | No type deduction (explicit type needed).  | **Type deduced** automatically in templates.         |
| **Standard Library Function** | `std::move`, `std::forward`               | `std::forward` to forward arguments in template functions. |
| **Example Use Case**      | Moving a resource from a temporary object. | Forwarding a parameter in a generic function (perfect forwarding).|


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