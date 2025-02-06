# Inline Functions

An **inline function** in C++ is a function that is expanded at the point of each call, rather than being executed through a regular function call. When a function is declared as `inline`, the compiler attempts to replace the function call with the actual code of the function, effectively "inlining" the function's code at the call site.

The main advantage of using inline functions is that it can lead to faster execution by eliminating the overhead associated with function calls, especially for small functions that are called frequently.

## Pros:

- **Faster execution**: Inline functions reduce the overhead of function calls, which can improve performance, particularly for small, frequently-called functions.
  
- **Code size reduction**: Inline functions can reduce the size of the executable code in some cases, as the function body is inserted at the call site. However, this can vary based on how many times the function is inlined.

- **Optimization opportunities**: Inline functions provide more opportunities for compiler optimizations, such as better instruction scheduling, loop unrolling, and constant folding.

## Cons:

- **Code bloat**: If inline functions are overused, particularly for large functions, it can lead to code bloat and increase the size of the executable. This happens because the function body is copied at each call site, which may result in a large increase in code size.

- **Compiler limitations**: The `inline` keyword is a suggestion to the compiler, not a command. The compiler may choose not to inline a function, especially if the function is too complex, contains recursion, or has control flow that makes inlining impractical.

- **Increased compile time**: Inlining can increase compile time, as the compiler needs to process and generate the function code at each call site, rather than simply handling a single function call.

---

## Additional Notes:
- Inline functions are most beneficial for small, simple functions, such as getter and setter methods, where the performance gain from avoiding function call overhead is significant.
- The `inline` keyword is particularly useful for header files that are included in multiple source files, as it avoids the need for multiple function definitions.


## Example

```cpp
#include <iostream>

inline int max(int a, int b) {
  return (a > b) ? a : b;
}

int main() {
  int x = 5, y = 10;
  int z = max(x, y);
  std::cout << "The maximum of " << x << " and " << y << " is " << z << std::endl;
  return 0;
}
```
## Example of execution time
```cpp
#include <iostream>
#include <chrono>

inline void func1(int a)
{
    a++;
}

void func2(int a)
{
    a++;
}

int main()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1E6; i++)
    {
        func1(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;


    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1E6; i++)
    {
        func2(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    
    return 0;
}
```
### output:
```
1941 // with inline
2018 // with function call
```
