## Basic operators
Uses Radians
```cpp
#include <cmath>
pow(val, 2);
sqrt(val);
sin(val);
cos(val);
tan(val);
```
## Random number
### Using C
```c
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate a random floating-point number in the range [0, 0.002)
    float num = ((float)rand() / RAND_MAX) * 0.002f;

    return 0;
}
```
### Using C++
```cpp
#include <cstdlib>
#include <iostream>
#include <ctime>

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random floating-point number in the range [0, 0.002)
    float num = ((float)std::rand() / RAND_MAX) * 0.002f;

    return 0;
}
```
