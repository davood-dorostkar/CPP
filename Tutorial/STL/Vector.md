### Initialization
by default the size is zero
```cpp
#include <vector>

std::vector<int> vec;
std::cout << vec.size(); // size is 0
```
### resize
```cpp
vec.resize(20); // size is 20
```
### make an iterator
it should be of the same type
```cpp
std::vector<int> vectorInts;  
std::vector<int>::iterator it;
```
### Assign
it puts data in the vector, and replaces old data.
```cpp
vectorInts.assign(how many times, value);
```
### iterating over vector
```cpp
for (it = vectorInts.begin(); it != vectorInts.end(); ++it)
    std::cout<<*it<<" ";
```
### Append data
adding data to the end of vector
```cpp
vectorInts.push_back(4);
```
### Insert data to specific location
first you should set the position. after `insert`, the iterator is not valid, so you should set it again for the next insert.
```cpp
it  = vectorInts.begin();
vectorInts.insert(it, -1);

it  = vectorInts.begin();
vectorInts.insert(it + 3, -2);
```
another method doing the same is `emplace`. Insert copies the values of the vector while emplace does an in-place insertion. The difference makes emplace more efficient than insert in special cases.
```cpp
it  = vectorInts.begin();
vectorInts.emplace(it + 3, -1);
```
### Clear all values
```cpp
vectorInts.clear();
```
### Delete specific values
```cpp
vectorInts.erase(location);
```
### delete a range
```cpp
vectorInts.erase(start, end);
```
### delete last element
```cpp
vectorInts.pop_back();
```