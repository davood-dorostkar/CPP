An inline function in C++ is a function that is expanded in place by the compiler where it is called, instead of being executed through a function call. The `inline` keyword is used to indicate to the compiler that a function should be inlined.

The main advantage of using inline functions is that it can lead to faster code execution, as the overhead of a function call is eliminated. This is especially beneficial for small functions that are called frequently in a program.

### Pros

1. Faster execution: Inline functions can reduce the overhead of function calls and improve performance, especially for small functions that are called frequently.

2. Code size reduction: Inline functions can reduce the size of the executable code, as the function code is inserted at the call site instead of being duplicated multiple times.

3. Optimization opportunities: Inline functions can provide opportunities for compiler optimizations, such as loop unrolling and constant folding.

### Cons

1. Code bloat: If inline functions are used excessively or for large functions, it can result in code bloat and increase the size of the executable code.

2. Compiler limitations: The use of inline functions is ultimately determined by the compiler, and not all functions may be successfully inlined, especially those with complex control flow or that are recursive.

3. Increased compile time: The inlining process can increase the compile time of the program, as the compiler needs to duplicate the function code at each call site.

### Example

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