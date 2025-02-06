# Exception Handling

## Syntax
```cpp
    try
    {
        // a code that may produce errors
    }
    catch (const std::exception &e)
    {
        std::cout << "e: " << e.what() << std::endl;
    }
```

## Exception types
the `std::exception` is the base class for handling exceptions. there are a variety of inherited classes for specific situations. if you know the type of possible error, you can use the corresponding class, otherwise use the general class.

## **Best Practices for Exception Handling**
- **Always catch exceptions by reference** to avoid slicing:
```cpp
catch (const std::exception& e)
```
- **Use specific exception types** where possible instead of `std::exception`.  
- **Provide meaningful error messages** using `e.what()`.  
- **Use `try-catch` blocks only where necessary**, don't overuse them.  


## **Most Important Exception Subclasses in C++**
C++ provides a hierarchy of exception classes under `std::exception`. The most commonly used exception subclasses are:

---

### **1. `std::exception` (Base Class)**

- **Base class for all standard exceptions**.
- Provides a `what()` method to retrieve an error message.
- Catching `std::exception&` allows handling all standard exceptions.


### **2. `std::logic_error` (Compile-Time Errors)**
Used for errors **that could have been avoided by proper logic in the program** (e.g., violations of preconditions).

#### **Common Subclasses:**
| Exception | Description |
|-----------|------------|
| `std::invalid_argument` | Used when an invalid argument is passed to a function. |
| `std::domain_error` | Used when a function is called with an argument outside its valid range. |
| `std::length_error` | Used when an operation exceeds the maximum allowable size (e.g., `std::vector::resize()`). |
| `std::out_of_range` | Used when an out-of-bounds access occurs (e.g., `std::vector::at(100)`). |

#### **Example:**
```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::out_of_range("Index is out of range!");
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}
```


### **3. `std::runtime_error` (Runtime Errors)**
Used for **errors that cannot be predicted at compile time**, such as invalid user input, system failures, or external conditions.

#### **Common Subclasses:**
| Exception | Description |
|-----------|------------|
| `std::range_error` | Used when a calculation produces a value outside the valid range. |
| `std::overflow_error` | Used when a mathematical operation results in overflow. |
| `std::underflow_error` | Used when a mathematical operation results in underflow. |

#### **Example:**
```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::runtime_error("Unexpected runtime failure!");
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}
```


### **4. `std::bad_alloc` (Memory Allocation Failure)**
- Thrown when `new` fails to allocate memory.
- Example:
```cpp
#include <iostream>
#include <new>  // std::bad_alloc

int main() {
    try {
        int* largeArray = new int[100000000000];  // Huge allocation
    } catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
    }
}
```

### **5. `std::bad_cast` (Failed `dynamic_cast`)**
- Thrown when an invalid `dynamic_cast` is attempted on a polymorphic type.
- Example:
```cpp
#include <iostream>
#include <typeinfo>

class Base { virtual void dummy() {} };
class Derived : public Base {};

int main() {
    try {
        Base base;
        Derived& d = dynamic_cast<Derived&>(base);  // Invalid cast
    } catch (const std::bad_cast& e) {
        std::cout << "Bad cast: " << e.what() << std::endl;
    }
}
```

### **6. `std::bad_typeid` (Using `typeid` on Null Pointer)**
- Thrown when `typeid(*ptr)` is used on a null pointer to a polymorphic object.
- Example:
```cpp
#include <iostream>
#include <typeinfo>

class Base { virtual void dummy() {} };

int main() {
    try {
        Base* ptr = nullptr;
        std::cout << typeid(*ptr).name() << std::endl;  // Invalid
    } catch (const std::bad_typeid& e) {
        std::cout << "Bad typeid: " << e.what() << std::endl;
    }
}
```

### **Summary Table**
| Exception Class | Description |
|----------------|-------------|
| `std::exception` | Base class for all exceptions. |
| `std::logic_error` | Errors caused by incorrect logic (compile-time). |
| `std::invalid_argument` | Invalid argument passed to a function. |
| `std::domain_error` | Value is outside the valid range for a function. |
| `std::length_error` | Size exceeds the allowed limit. |
| `std::out_of_range` | Index is out of valid bounds (e.g., `std::vector::at()`). |
| `std::runtime_error` | Errors that occur at runtime. |
| `std::range_error` | Mathematical computation produced an out-of-range value. |
| `std::overflow_error` | Arithmetic overflow occurred. |
| `std::underflow_error` | Arithmetic underflow occurred. |
| `std::bad_alloc` | Memory allocation failed (`new` failure). |
| `std::bad_cast` | Invalid `dynamic_cast` on a polymorphic type. |
| `std::bad_typeid` | `typeid` used on a null pointer. |
