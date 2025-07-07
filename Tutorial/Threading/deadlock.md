# Deadlock, `std::lock_guard`, `std::scoped_lock`

**Deadlock** is a situation where threads are permanently blocked because one of them **never releases a lock**. This is a critical issue in concurrent programming, often caused by:

- **forgetting to unlock** a `std::mutex`, especially in the presence of **exceptions**.
- creating multiple locks that each depend on the other, which makes **circular waits**

## 🧪 1. Deadlocks from unreleased locks
To solve this, we use **`std::lock_guard`**, a C++ RAII wrapper that ensures **mutexes are automatically unlocked** when the `lock_guard` goes out of scope — even if an exception is thrown.

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


### 🧭 Extra Tip: Where to Place Lock Guards?

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

### ✅ Conclusion

Using `std::lock_guard` is the **best practice** for locking in C++. It:

* Prevents deadlocks,
* Makes code **cleaner and safer**,
* Ensures locks are released **even when exceptions happen**.


## 🪤 2. Deadlock from Circular Waits

Sometimes, deadlock come from threads **locking mutexes in different orders**.

This is a classic mistake in concurrent programming — and it **cannot be solved with `lock_guard` alone**.

### ⚠️ Problem: Inconsistent Lock Order

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void thread1()
{
    std::cout << "Thread 1 acquired mutex 1" << std::endl;
    mutex1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread 1 trying to acquire mutex 2" << std::endl;
    mutex2.lock();
    std::cout << "Thread 1 acquired mutex 2" << std::endl;

    // Critical section...
    mutex2.unlock();
    mutex1.unlock();
}

void thread2()
{
    std::cout << "Thread 2 acquired mutex 2" << std::endl;
    mutex2.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread 2 trying to acquire mutex 1" << std::endl;
    mutex1.lock();
    std::cout << "Thread 2 acquired mutex 1" << std::endl;

    // Critical section...
    mutex1.unlock();
    mutex2.unlock();
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join(); t2.join();
    return 0;
}
```
### 💡 Output 
execute: 
```bash
g++ -std=c++17 deadlock2.cpp -o deadlock2 -lpthread && ./deadlock2 && rm deadlock2
```

### 💥 What Happens?

1. **Thread 1** locks `mutex1` and waits for `mutex2`
2. **Thread 2** locks `mutex2` and waits for `mutex1`
3. Both are waiting for each other **forever** — this is **deadlock by circular wait**!

⛔ `lock_guard` **won’t help** here, because both locks are correctly released — the issue is **order of acquisition**.

---

## ✅ Fix: Use `std::scoped_lock` or Always Lock in Same Order

You can either:

* 💡 **Always lock mutexes in the same order**, OR
* ✅ Use **`std::scoped_lock`** (C++17), which atomically locks multiple mutexes and avoids deadlock:

```cpp
void thread_safe()
{
    std::scoped_lock lock(mutex1, mutex2); // locks both safely, in consistent order
    // Critical section
}
```

## 🔍 Key Concepts

| Concept                       | Description                                                                                  |
| ----------------------------- | -------------------------------------------------------------------------------------------- |
| 🧊 **Deadlock**               | When a thread never releases a lock, blocking others indefinitely                            |
| ⚠️ Manual `lock()`/`unlock()` | Error-prone — if an exception occurs or `unlock()` is forgotten, your app can hang           |
| 🛡️ `std::lock_guard`         | RAII-based helper that **automatically unlocks** the mutex at the end of the scope           |
| 🪤 **Circular wait**   | Each thread waits on a lock held by another — a perfect deadlock cycle              |
| 🛡️ `std::scoped_lock` | C++17 utility that atomically locks multiple mutexes in **deadlock-safe order**     |
| 🧠 RAII                       | *Resource Acquisition Is Initialization*: release resources when an object goes out of scope |


## 🧠 Takeaway
let the standard library help you.

✅ Use:

* `std::lock_guard` for **single mutex safety**
* `std::scoped_lock` for **multiple mutex safety**

## 💬 Read more
other smart concurrency patterns like `std::unique_lock` or `std::atomic`!