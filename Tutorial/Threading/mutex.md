# Mutex

## 🧵 Summary: Handling Shared Data in Multithreaded C++ with `std::mutex`

Here we introduces the classic problem of **multiple threads accessing and modifying a shared variable**, which can lead to **race conditions** and **non-deterministic behavior**. The solution presented is to use `std::mutex` — a synchronization primitive that ensures **only one thread at a time** can access the critical section where shared data is manipulated.

---

## 🧪 Tutorial: Fixing Race Conditions Using `std::mutex`

### 🔧 Required Headers

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
```

---

### ❌ Race Condition Example (No Mutex)

```cpp
#include <iostream>
#include <thread>
#include <vector>

int shared_value = 0;

void increment_shared_value() {
    shared_value = shared_value + 1;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; i++) {
        threads.push_back(increment_shared_value);
    }

    for (auto& t : threads) t.join();

    std::cout << "Final value: " << shared_value << std::endl;
    return 0;
}
```

- 🧨 **Expected?** 100
- 🧨 **Actual?** Varies (e.g. 96, 99, 100)
- ⚠️ This is a **data race**: threads are reading and writing to `shared_value` simultaneously.

---

### ✅ Safe Version with `std::mutex`

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int shared_value = 0;
std::mutex glock;

void increment_shared_value() {
    glock.lock();
    shared_value = shared_value + 1;
    glock.unlock();
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; ++i) {
        threads.push_back(increment_shared_value);
    }

    for (auto& t : threads) t.join();

    std::cout << "Final value: " << shared_value << std::endl;
    return 0;
}
```

✅ Alternative: use **RAII** with `std::lock_guard`:

```cpp
void increment_shared_value() {
    std::lock_guard<std::mutex> guard(g_lock); // Auto-lock and unlock
    shared_value += 1;
}
```

### ⚙️ Compile & Run

```bash
g++ -std=c++17 mutex.cpp -o mutex -lpthread && ./mutex && rm mutex
```

✅ Always prints `1000` now — the **race condition is fixed**!

---

## 💡 What You Learned

| Concept               | Description                                                                     |
| --------------------- | ------------------------------------------------------------------------------- |
| 🧠 **Race Condition** | Two or more threads accessing shared data at the same time without coordination |
| 🔒 `std::mutex`       | Ensures mutual exclusion (only one thread can enter the critical section)       |
| 🚪 Critical Section   | The part of code that accesses shared resources and must be protected           |
| ✅ `std::lock_guard`   | Safer alternative that auto-unlocks when it goes out of scope (RAII)            |

---

### 🖼 Visual Analogy

* Threads = people
* `shared_value` = room
* `std::mutex` = key to the room
* Only **one person** can hold the key at a time; others must **wait** outside

---

### 💭 Did We Slow Down the Program?

Yes — slightly. Threads **wait** for access to shared data. But often, only **a small part** of their work needs synchronization. You can let them run other non-critical code **outside the lock**.

```cpp
void increment_shared_value() {
    // Unprotected part (can run concurrently)
    std::cout << "Doing some unrelated work\n";

    // Critical section
    glock.lock();
    shared_value = shared_value + 1;
    glock.unlock();
}
```

---

## 🔚 Conclusion

Using `std::mutex` ensures **correctness** in concurrent programs with shared data. Always protect critical sections to avoid race conditions. In future lessons, you'll learn more advanced synchronization tools — but `mutex` is a fundamental building block of multithreaded C++.