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

### size vs capacity

size is the amound of data currently occupied in vector, while capacity is the total size of the vector. keep in mind: the vector's capacity is handled dinamically by C++ and is always larger than the current data size. a rule of thumb is that it becomes twice when you add new element and the vector needs to get larger. (although it is not that easy)

```cpp
vec.size() // size is 3
vec.capacity() // capacity is 6
```

### Append data

adding data to the end of vector

```cpp
vectorInts.push_back(4);
```

### Assign

it puts data in the vector, and replaces old data.

```cpp
vectorInts.assign(how many times, value);
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


### Understanding std::vector::end()

`numbers.end()` returns an iterator pointing to one past the last element of the vector. This is often referred to as the `past-the-end` iterator.

It is important to note that the "past-the-end" iterator does not point to a valid element; dereferencing it is `undefined behavior`.

print the last element of the vector:
```cpp
std::vector<int> numbers = {1, 3, 5, 7, 9, 8};  
std::cout << *(numbers.end() - 1)  << std::endl;  
// console: 8
```

## Iterators
### make an iterator

it should be of the same type

```cpp
std::vector<int> vectorInts;
std::vector<int>::iterator it;
```

### iterating over vector

```cpp
for (it = vectorInts.begin(); it != vectorInts.end(); ++it)
    std::cout<<*it<<" ";
```
## Loop over vector
you can use several methods to loop over a vector. good news is that vector is empty-safe; means that if it is empty, it will work as expected and you dont need to check it:
```cpp
std::vector<int> vec;
for (const auto &item : vec)
{
    std::cout << item;
}
std::cout << "end" << std::endl;
```