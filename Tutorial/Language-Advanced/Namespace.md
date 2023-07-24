A namespace in C++ is a way to group related identifiers (such as functions, classes, and variables) under a unique name, to avoid naming conflicts and to make it easier to organize and maintain code.
## using namespace
```cpp
#include <iostream>

using namespace std;

int main() {
    cout << "Hello, world!" << endl;
    return 0;
}
```
## using part of a namespace
```cpp
#include <iostream>

using std::cout;
using std::endl;

int main() {
    cout << "Hello, world!" << endl;
    return 0;
}
```
## Define a namespace
```cpp
// mymath.h

namespace mymath {
    class Calculator {
    public:
        int add(int a, int b);
        int subtract(int a, int b);
    };
}
```
```cpp
// mymath.cpp

#include "mymath.h"

namespace mymath {
    int Calculator::add(int a, int b) {
        return a + b;
    }

    int Calculator::subtract(int a, int b) {
        return a - b;
    }
}
```
```cpp
// main.cpp

#include <iostream>
#include "mymath.h"

int main() {
    mymath::Calculator calculator;
    std::cout << "3 + 4 = " << calculator.add(3, 4) << std::endl;
    std::cout << "5 - 2 = " << calculator.subtract(5, 2) << std::endl;
    return 0;
}
```