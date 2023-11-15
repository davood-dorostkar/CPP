# Pair
In C++, a special template allows you to pair one type with any other type as a single object.

```cpp
#include <utility>
std::pair<std::string, int> myPair;
```
## Definition after declaration
There are 3 ways to define a pair:

### using `first` and `second`
```cpp
myPair.first = "Hello, this is the string element.";
myPair.second = 42;
```
### using `make_pair`
```cpp
std::pair<std::string, int> anotherPair = std::make_pair("sevens", 777);
```
### using brackets

Since C++11, you can use a generic initializer list in brackets {...} to initialize a pair. You cannot use auto to define it because C++ uses this kind of generic syntax to initialize many STL types besides pairs.

```cpp
std::pair<std::string, int> anotherPair = {"sevens", 777};
```
## Define and declare
here you have 4 options. all are the same:

```cpp
std::pair<int,int> point1 = std::pair<int,int>(1,2);
std::pair<int,int> point2 = std::make_pair(1,2);
auto point3 = std::pair<int,int>(1,2);
std::pair<int,int> point4 = {1,2};
```