# `std::async` & `std::future` 

`std::async` is a C++11 feature that launches a **function asynchronously**—meaning it runs on a separate thread without blocking the main thread. The result of this asynchronous task is stored in a **`std::future`** object, which acts as a placeholder for a value that becomes available later.

This mechanism is useful when:

* You want to run background computations.
* You only need synchronization **when retrieving the result**, not during the computation.

---

## 📘 Tutorial: Using `std::async` and `std::future`

### 🔧 Code

```cpp
#include <iostream>
#include <future>

int square(int x){
    return x * x;
}

int main(){
    std::future<int> asyncFunction = std::async(&square, 12);

    // Do other work while async task runs
    for(int i = 0; i < 10; ++i){
        std::cout << square(i) << std::endl;
    }

    // Block only when result is needed
    int result = asyncFunction.get();

    std::cout << "result is: " << result << std::endl;
    return 0;
}
```
**Usage**:
```bash
g++ -std=c++17 -lpthread async-future.cpp -o async-future && ./async-future && rm async-future
```

### 🧠 How it works

1. ✅ `std::async(&square, 12)` starts `square(12)` on a separate thread.
2. ✅ Main thread continues and does other work (`square(i)` loop).
3. 🕒 When we call `.get()`, the main thread **waits** if the result isn't ready.
4. ✅ Once ready, the result is retrieved and printed.

⚠️ `.get()` blocks **only at the point** where the result is needed, improving efficiency.

---

### ✅ Key Concepts Recap

| Concept          | Explanation                                               |
| ---------------- | --------------------------------------------------------- |
| `std::async`     | Launches a function on a separate thread (async task)     |
| `std::future<T>` | Represents a value that will be available in the future   |
| `.get()`         | Blocks until the async result is ready, then retrieves it |
| Use Case         | Background computation + on-demand result retrieval       |

---

### 💡 Real-World Use Cases

* Background data processing
* Lazy evaluation of expensive computations
* Lightweight concurrency without explicit thread management
