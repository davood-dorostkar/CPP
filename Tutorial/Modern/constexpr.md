# constexpr

## Introduction to `constexpr` in C++ 

The `constexpr` keyword, introduced in C++11, enables **compile-time computation**, improving performance by eliminating runtime calculations. It can be applied to **functions, variables, constructors, and even data structures**, ensuring that values are evaluated at compile-time whenever possible. 

Before `constexpr`, developers relied on `const` variables or preprocessor macros, which lacked compile-time function evaluation. `constexpr` fills this gap by enabling functions, variables, and even complex data structures to be computed entirely at compile time, ensuring **both better performance and improved code safety**.

Over the years, C++14, C++17, and C++20 have expanded its capabilities, making it a powerful tool for **optimization, metaprogramming, and embedded systems**. Mastering `constexpr` allows developers to write **faster, safer, and more efficient** code.



## 1. `constexpr` Variables
variables can be declared as `constexpr`, ensuring they are **constant expressions** known at compile-time.

```cpp
constexpr double pi = 3.141592653589793;
constexpr int max_size = 100;
```
🔹 This is more restrictive than `const` because the value **must be evaluable at compile-time**.

---

## 2. `constexpr` Constructors
C++11 allows **constructors** to be marked as `constexpr`, enabling compile-time object initialization.

```cpp
struct Point {
    constexpr Point(int x, int y) : x_(x), y_(y) {}
    constexpr int getX() const { return x_; }
    constexpr int getY() const { return y_; }

private:
    int x_, y_;
};

constexpr Point p(3, 4); // Object initialized at compile-time
constexpr int x = p.getX(); // Compile-time retrieval
```

- `constexpr` constructors are useful in **mathematical libraries, embedded systems, and constexpr data structures**.

---

## 3. `constexpr` Arrays and Lookup Tables
Using `constexpr` for arrays allows **precomputed lookup tables**, eliminating costly calculations at runtime.

```cpp
constexpr int factorial_table[] = {1, 1, 2, 6, 24, 120, 720}; // Precomputed values
constexpr int fact_4 = factorial_table[4]; // Computed at compile-time
```

🔹 Useful for **fast function evaluation, hash tables, and mathematical computations**.

---

## 4. `constexpr` Strings (`std::string_view`)
In C++20, `std::string_view` enables compile-time string manipulations.

```cpp
#include <string_view>

constexpr std::string_view hello = "Hello, constexpr!";
constexpr char first_char = hello[0]; // 'H'
```

🔹 Helps in **compile-time string processing and static configurations**.

---

## 5. `constexpr` Data Structures
From **C++20**, `std::vector`, `std::array`, and even `std::map` can be used in `constexpr` contexts.

```cpp
#include <array>

constexpr std::array<int, 3> nums = {1, 2, 3};
constexpr int first = nums[0]; // Compile-time access
```

🔹 Useful for **embedded systems and constexpr-based computations**.

---

## 6. `if constexpr` (Compile-Time Branching)
Introduced in **C++17**, `if constexpr` enables conditional compilation.

```cpp
template<typename T>
constexpr auto get_value(T val) {
    if constexpr (std::is_integral_v<T>) {
        return val * 2; // Compile-time optimization for integers
    } else {
        return val + val; // Different logic for non-integers
    }
}
```

🔹 **Optimizes template-based code**, allowing different execution paths for different types.

---


## 7. `constexpr` Functions

### Basic Syntax
A `constexpr` function is declared using the `constexpr` keyword before the return type.

```cpp
constexpr int square(int x) {
    return x * x;
}

constexpr int result = square(5); // Computed at compile-time
```

If the argument is a **constant expression**, the computation happens at compile-time.

---

### Key Features
#### 1. Compile-Time Evaluation  
   If all arguments are constant, the function is evaluated at compile-time.
   
#### 2. Constant Expressions  
   Useful in **array sizes, template arguments, and static variables**.

#### 3. Performance Optimization  
   Shifts computations from **runtime to compile-time**, reducing execution time.

```cpp
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}
constexpr int fib5 = fibonacci(5); // Computed at compile-time
```

---

### Use Cases
#### 1. Compile-Time Array Sizes
```cpp
constexpr int arr_size = 10;
int arr[arr_size]; // Allowed because arr_size is a constant expression
```

#### 2. Compile-Time Template Parameters
```cpp
template<int N>
constexpr int square() {
    return N * N;
}

constexpr int value = square<4>(); // Compile-time calculation
```

#### 3. Catching Errors at Compile-Time
If a `constexpr` function is passed a non-constant variable, compilation fails.

```cpp
int x = 5;
constexpr int result = square(x); // Error: x is not a constant expression
```

---

### Limitations in C++11
#### 1. Limited Control Structures  
   - Only **`if` statements and recursion** were allowed.
   - Loops (`for`, `while`) were **not** permitted.

#### 2. No Dynamic Memory Allocation
   ```cpp
   constexpr int* allocate() {
       return new int(5); // Error in C++11
   }
   ```

#### 3. No Exceptions
   - `constexpr` functions **cannot throw exceptions** in C++11.

---

### Enhancements in Later C++ Versions
#### C++14
- **Allowed Loops**  
  ```cpp
  constexpr int factorial(int n) {
      int result = 1;
      for (int i = 1; i <= n; ++i) {
          result *= i;
      }
      return result;
  }
  ```

#### C++17
- **Allowed Dynamic Memory Allocation**
  ```cpp
  constexpr int* create_array(int size) {
      return new int[size]; // Allowed in C++17
  }
  ```

- **`constexpr` Lambdas**
  ```cpp
  constexpr auto square = [](int x) { return x * x; };
  ```

#### C++20 & C++23
- **`if constexpr` for Compile-Time Branching**
  ```cpp
  constexpr int max(int a, int b) {
      if constexpr (a > b) return a;
      else return b;
  }
  ```

- **Allowed Containers like `std::vector` in `constexpr` Contexts**  

---

### Best Practices
1. **Keep functions simple** to improve maintainability.  
2. **Use `constexpr` for constants**, mathematical computations, and configuration values.  
3. **Leverage `constexpr` for metaprogramming**, ensuring efficient template-based computations.  