- It is a LIFO DS
- Main operations of stack:
  - create: create an empty stack
  - push: add data to top
  - pop: remove data from top
  - empty: is it empty?
- There is a stack implementation in C++
- unlike queue, a singly linked list is sufficient to implement stack

```cpp
#include <stack>

std::stack<int> s; // create
s.push(3); // add item
s.push(6);

std::cout << s.top(); // show top item
std::cout << s.empty();

s.pop(); // remove top element
```

![](/images/stack.png)

### Internal Implementation

It can be either implemented with `array` or `singly linked list`.

|        | Array                                           | Linked List |
| ------ | ----------------------------------------------- | ----------- |
| create | O(1)                                            | O(1)        |
| push   | O(1) [occasionally need to double the capacity] | O(1)        |
| pop    | O(1) [occasionally need to shrink the capacity] | O(1)        |
| empty  | O(1)                                            | O(1)        |
