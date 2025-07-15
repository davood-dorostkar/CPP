# Synchronization with Condition Variables

In multithreading, when multiple threads try to access a **critical section** protected by a mutex, only one thread can access it at a time. The rest either spin (wasting CPU cycles) or **wait** more efficiently using synchronization primitives.

A **condition variable** in C++ allows one thread to **block** (sleep) until another thread notifies it. This avoids wasteful CPU usage caused by polling or spin-locking.

The key components used:

* A **`mutex`** for mutual exclusion.
* A **`condition_variable`** to signal changes.
* A **shared boolean flag** (e.g., `notified`) to represent the condition.
* A **`unique_lock`** for flexible locking/unlocking (needed with `condition_variable`).

## 📘 Tutorial: Using `std::condition_variable` in C++

We demonstrate a **worker thread** that does some work and notifies a **reporting thread** once it's done.

### 🔧 Code Breakdown

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main(){
    int result = 0;
    bool notified = false;

    // 🧾 Reporting thread (waits for notification)
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified){
            gConditionVariable.wait(lock);  // Waits until notified (goes to sleep mode)
        }
        std::cout << "Reporter, result is: " << result << std::endl;
    });

    // 🔧 Working thread (does work and notifies)
    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock);
        result = 42 + 1 + 7;  // Do some computation
        notified = true;     // Update shared state
        std::this_thread::sleep_for(std::chrono::seconds(3));  
        std::cout << "Work complete\n";
        gConditionVariable.notify_one();  // Notify the waiting thread
    });

    reporter.join();
    worker.join();

    std::cout << "Program complete" << std::endl;
    return 0;
}
```
⚠️ Pay attention to the fact that the same lock (`gLock`) is used for both threads. 

But the way we acquire that lock can be different. In fact the thread that is `waiting` on a lock (here the `reporter`) needs to be used with `unique_lock`, because it provides more intelligent features than the simple `lock_guard`, like the ability to sleep. 

However, the `worker` thread doesn't necessarily need a unique_lock because it is not using any of its features. As a result the lock in the worker can be defined with either `lock_guard` or `unique_lock`, and the first one is prefered here because it is simpler.

**Usage**:
```bash
g++ -std=c++17 -lpthread condition-var.cpp -o condition && ./condition && rm condition
```

---

### 💡 Use Cases

* **Producer-Consumer** model
* Thread coordination (e.g., wait until config is loaded)
* Event-based systems
