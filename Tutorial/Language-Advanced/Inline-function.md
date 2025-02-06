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
## Code Size Explanation
Inline functions don't always reduce code size—in fact, they can increase the size if used excessively. However, in some cases, they may reduce code size, particularly when they avoid function call overhead and prevent the need for multiple function definitions.

### Example 1: Without Inline Functions (Regular Function Call)

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = add(3, 5);
    int y = add(7, 9);
    std::cout << x << " " << y << std::endl;
    return 0;
}
```

In this case, the `add` function has a simple task of adding two numbers. If this function is not inline, it will have an entry and exit point for each call. The compiler generates machine code for the function and will need to generate a jump to the function's memory location each time it is called. The machine code would look something like this:

1. **Function call (to `add`)**: The program needs to set up the stack and jump to the location of the `add` function.
2. **Return from function**: The program will return to the original call site after performing the addition.

While the function is small, this involves function call overhead, which increases the size of the generated machine code.

### Example 2: With Inline Function

Now, if we declare the function as `inline`:

```cpp
#include <iostream>

inline int add(int a, int b) {
    return a + b;
}

int main() {
    int x = add(3, 5);
    int y = add(7, 9);
    std::cout << x << " " << y << std::endl;
    return 0;
}
```

In this case, the compiler will try to replace the function call with the function's code directly at the call site. So instead of generating a call to `add()`, it will substitute the function body directly in the code, like this:

```cpp
int main() {
    int x = 3 + 5;   // Inline replacement of add(3, 5)
    int y = 7 + 9;   // Inline replacement of add(7, 9)
    std::cout << x << " " << y << std::endl;
    return 0;
}
```

### Code Size Consideration:
- **Without `inline`**: You have the overhead of a function call. The machine code will include instructions to handle the function call, parameter passing, and returning from the function. This adds extra bytes to your code.
  
- **With `inline`**: The function’s body is directly inserted into the places where the function is called. This eliminates the overhead of setting up and returning from the function call. The machine code is more compact because there are no function call mechanisms—just the addition operations directly in the `main()` function.

### When Inline Functions Can Reduce Code Size:
- **Small functions**: If the function is very small, like `add()`, inlining it can avoid the overhead of function calls and thus make the program faster and, in some cases, even reduce the size by removing function prologues, epilogues, and jump instructions.
- **Frequent calls**: For very frequently called small functions (e.g., simple math or getter functions), inlining could reduce the need to have the same small function generated in multiple places, thereby reducing overhead.

### When Inline Functions Can Increase Code Size:
- **Larger functions**: If you inline a large function, you might be duplicating a significant amount of code at each call site, increasing the total size of the executable.
- **Multiple call sites**: If the function is used in many places, inlining may lead to a larger executable since the function’s body is duplicated at each call site.
