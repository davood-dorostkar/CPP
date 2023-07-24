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
### Random number
```cpp
#include <time.h> 
#include <cstdlib>
    srand(time(NULL));  //set the seed for the random number generator
    target = rand() %100 + 1; 
```