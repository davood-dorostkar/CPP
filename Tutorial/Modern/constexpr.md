# constexpr

## `constexpr` Functions in C++

Introduced in C++11, `constexpr` allows functions to be evaluated at **compile-time**, reducing runtime overhead. It’s particularly useful for pre-calculating values in **array sizes, template parameters, and initialization of constants**.

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

---

### Conclusion
The introduction of `constexpr` in C++11 revolutionized compile-time computation. With improvements in later versions (C++14, C++17, C++20), `constexpr` has become a powerful tool, **optimizing performance and improving code safety**. Mastering `constexpr` is essential for modern C++ development.