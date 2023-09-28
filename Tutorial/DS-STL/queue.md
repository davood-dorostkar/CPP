- A queue is a FIFO DS
- we have a dedicated DS in STL for queue

```cpp
#include <queue>

std::queue<int> q;
q.push(1); // enqueue an element
q.push(2);

std::cout << q.front(); // show front element

q.pop(); // dequeue an element
```

![](/images/queue.png)
