### `scanf` (C-style input)
it has some limitations:
* it is not type-safe
* you should handle the length of input string
* does not have error-handling
```cpp
int newVar;
std::scanf("%d",&newVar);
```
### `cin` limitations
1. it does not accept white space in strings, once it reaches a white space it assumes the input is finished
2. it does not support type conversion, the input must be in the defined variable type
3. it accepts only 1 line at a time
### read a full line from `cin`
even if it consists of white spaces
```cpp
std::string var;
std::getline(std::cin, var);
```
### convert `cin` input to data types
[sstream reference](https://cplusplus.com/reference/sstream/)
```cpp
#include <sstream>

    std::string lengthAsString;
    float length;

    std::cout << "enter the length\n";
    std::getline(std::cin, lengthAsString);

    std::stringstream(lengthAsString) >> length;

    std::cout << length << std::endl;
```
### Print decimal data
```cpp
#include <iomanip> 
court << std::fixed << std::setprecision(number of decimal places)
```
```cpp
cout << fixed<<setprecision(9)<< Number << endl;
```
### fix the output width:
```cpp
#include <iomanip>
Std::cout << “double” << std::setw(10) << “int” << std::endl;
```
> usage: the width that you defined= some white space + the next item. in the example above, there will be **7 spaces** + **int** = 10 width.