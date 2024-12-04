# Struct
A `struct` (short for "structure") is a user-defined data type in C and C++ that groups together variables (called members) of different types under a single name. It is similar to a class in C++, but with key differences in behavior and usage.

## In C
- `struct` is used for grouping related data together.
- All members of a `struct` are **public** by default.
- It does not support features like member functions or access specifiers.
- To define a variable of the `struct` type in older versions of C, you need to prefix it with the `struct` keyword (unless you define a [typedef](/Tutorial/Language-Intermediate/typedef.md#typedef-usage-with-struct)).

### Syntax
```c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    struct Point p1 = {10, 20}; // Initialization
    printf("Point: (%d, %d)\n", p1.x, p1.y);
    return 0;
}
```

## In C++
- `struct` is similar to a class but has **public** members by default, whereas members of a class are **private** by default.
- It can include methods (functions), constructors, destructors, and even access specifiers.
- C++ `struct` supports all object-oriented programming features.

### Syntax
```cpp
#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;

    // Constructor
    Point(int a, int b) : x(a), y(b) {}

    // Member function
    void display() const {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1(10, 20); // Initialization using constructor
    p1.display();
    return 0;
}
```

### Key Features in C++
- Functions and methods can be included.
- Supports inheritance and polymorphism (just like classes).
- Can use access specifiers (`public`, `private`, `protected`) to control access to members.

## Differences Between `struct` in C and C++

| Feature               | C `struct`                     | C++ `struct`                    |
|-----------------------|---------------------------------|----------------------------------|
| Default member access | `public`                       | `public`                        |
| Methods/Functions     | Not allowed                    | Allowed                         |
| Constructors          | Not allowed                    | Allowed                         |
| Inheritance           | Not supported                  | Supported                       |
| Type usage            | `struct` keyword required to declare a variable (e.g., `struct Point p;`) | No need for `struct` keyword (e.g., `Point p;`) |

## Anonymous vs Named struct

### Anonymous `struct`
```c
struct 
{
    unsigned char l1:1;
    unsigned char l2:1;
    unsigned char l3:1;
} levels;
```

- The `struct` is **anonymous**, meaning it does not have a name.
- An instance of the `struct` is directly declared as `levels` after its definition.
- You cannot create another instance of this `struct` because it lacks a type name.


### Named `struct`
```c
struct levels
{
    unsigned char l1:1;
    unsigned char l2:1;
    unsigned char l3:1;
};
```

- The `struct` is **named**, with the type name `levels`.
- You can use `levels` to declare multiple instances of this structure later.

### Summary Anonymous vs Named

| Feature                  | Anonymous `struct`                      | Named `struct`                           |
|--------------------------|------------------------------------------|------------------------------------------|
| Definition Reusability   | Cannot create new instances             | Can create multiple instances            |
| Instance Declaration     | Must declare the instance immediately   | Instances can be declared anywhere later |
| Typedef Compatibility    | Cannot use `typedef` to simplify usage  | Can use `typedef` for cleaner code       |
