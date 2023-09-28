- A queue is a FIFO DS
- we have a dedicated DS in STL for queue
- main operations for a queue:
  - create: create an empty queue
  - push: add data to the back
  - pop: remove data from front
  - empty: it is empty?

```cpp
#include <queue>

std::queue<int> q; // create
q.push(1); // enqueue an element
q.push(2);

std::cout << q.front(); // show front element
std::cout << q.empty();

q.pop(); // dequeue an element
```

![](/images/queue.png)

### Internal Implementation

It can be either implemented with `array` or `doubly linked list`.

|        | Array                                           | Linked List |
| ------ | ----------------------------------------------- | ----------- |
| create | O(1)                                            | O(1)        |
| push   | O(1) [occasionally need to double the capacity] | O(1)        |
| pop    | O(1) [occasionally need to shrink the capacity] | O(1)        |
| empty  | O(1)                                            | O(1)        |
