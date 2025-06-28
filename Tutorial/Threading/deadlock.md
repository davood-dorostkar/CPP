# Deadlock and `std::lock_guard`

## 🧊 Summary: Avoiding Deadlocks with `std::lock_guard` (RAII in Multithreading)

**deadlock** is a situation where threads are permanently blocked because one of them **never releases a lock**. This is a critical issue in concurrent programming, often caused by **forgetting to unlock** a `std::mutex`, especially in the presence of **exceptions**.

To solve this, we use **`std::lock_guard`**, a C++ RAII wrapper that ensures **mutexes are automatically unlocked** when the `lock_guard` goes out of scope — even if an exception is thrown.

## 🧪 Tutorial: Preventing Deadlocks Using `std::lock_guard`

### ❌ Problem: Manual Locking with Missing Unlock

```cpp
std::mutex gLock;
static int shared_value = 0;

void increment_shared_value() {
    gLock.lock();
    shared_value += 1;
    // gLock.unlock(); ← 🔥 If this is forgotten or skipped (e.g., due to an exception), you get a DEADLOCK
}
```

**What happens?**

* One thread acquires the lock but **never releases** it.
* All other threads are **blocked forever** — the program freezes.

---

### ⚠️ Even Worse: Exception Before Unlock

```cpp
void increment_shared_value() {
    gLock.lock();
    try
    {
        shared_value += 1;
        throw "dangerous... abort"; // 🔥 Unlock never called
    }
    catch(...)
    {
        std::cout << "handle exception\n";
        return;
    }
    gLock.unlock(); // never reached
}
```

---

### ✅ Fix: Use `std::lock_guard` (RAII Approach)

```cpp
void increment_shared_value() {
    std::lock_guard<std::mutex> lockGuard(gLock);
    shared_value += 1;
    // Lock is automatically released when guard goes out of scope
    // you can also include the try-catch here without issues
}
```

---

### 🧵 Full Example: Safe, Exception-Proof Threading

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;
static int shared_value = 0;

void increment_shared_value() {
    std::lock_guard<std::mutex> guard(gLock);
    shared_value += 1;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; ++i) {
        threads.push_back(std::thread(increment_shared_value));
    }

    for (auto& t : threads) t.join();

    std::cout << "Final shared value: " << shared_value << std::endl;
    return 0;
}
```

### 💡 Output (Always)
execute: 
```bash
g++ -std=c++17 deadlock.cpp -o deadlock -lpthread && ./deadlock && rm deadlock
```

```
Final shared value: 1000
```

🧠 Even if exceptions are thrown, the `mutex` is correctly released thanks to `lock_guard`.

---

## 🔍 Key Concepts

| Concept                       | Description                                                                                  |
| ----------------------------- | -------------------------------------------------------------------------------------------- |
| 🧊 **Deadlock**               | When a thread never releases a lock, blocking others indefinitely                            |
| ⚠️ Manual `lock()`/`unlock()` | Error-prone — if an exception occurs or `unlock()` is forgotten, your app can hang           |
| 🛡️ `std::lock_guard`         | RAII-based helper that **automatically unlocks** the mutex at the end of the scope           |
| 🧠 RAII                       | *Resource Acquisition Is Initialization*: release resources when an object goes out of scope |

---

## 🧭 Extra Tip: Where to Place Lock Guards?

Lock guards should **cover only the code that needs synchronization** — the **critical section**:

```cpp
void worker() {
    std::cout << "Doing unrelated work\n";  // outside lock

    {
        std::lock_guard<std::mutex> guard(gLock);
        shared_value += 1;  // critical section
    }

    std::cout << "More unrelated work\n";  // outside lock
}
```

---

## ✅ Conclusion

Using `std::lock_guard` is the **best practice** for locking in C++. It:

* Prevents deadlocks,
* Makes code **cleaner and safer**,
* Ensures locks are released **even when exceptions happen**.

## 💬 Read more
`std::scoped_lock` (for multiple mutexes) or other smart concurrency patterns like `std::unique_lock` or `std::atomic`!
