# Starvation

**Starvation** happens when a thread is **perpetually denied access to a shared resource**, even though it remains active and ready. This typically occurs because other threads continuously grab the resource first.

## 🔍 Example: Starvation in Action

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;

void thread1() {
    while (true) {
        mutex.lock();
        std::cout << "Thread 1 acquired mutex" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mutex.unlock();
    }
}

void thread2() {
    while (true) {
        std::cout << "Thread 2 trying to acquire mutex" << std::endl;
        mutex.lock();
        std::cout << "Thread 2 acquired mutex" << std::endl;
        mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
```

### 🧠 Behavior

* `thread1()` keeps **locking and unlocking the mutex quickly and frequently** (every 100ms).
* `thread2()` tries to acquire the mutex every 500ms.
* Because `thread1` is always ready and **re-acquires the mutex before `thread2` gets a chance**, `thread2` often **fails to acquire the lock in time**, and ends up **starving**.

---

### 🔄 Output Sample

```
Thread 2 trying to acquire mutex
Thread 1 acquired mutex
Thread 1 acquired mutex
Thread 1 acquired mutex
Thread 1 acquired mutex
Thread 1 acquired mutex
...
```

Notice how **`Thread 2` rarely (or never) prints "acquired mutex"**, even though it's actively trying. This is classic starvation.


## 🔍 Why thread2 tries only once?

Because **`thread2` is blocked on `mutex.lock()` and never gets past it again**. It printed `"Thread 2 trying to acquire mutex"` once, then got **stuck** trying to acquire the mutex — and never got the chance to print anything else.  

Because `mutex.lock()` is a **blocking call** — it doesn’t return until it **acquires the mutex**. And since `thread1` keeps winning the race, `thread2` never returns from that call.


### 🧠 Execution Steps:

1. `thread2` starts and prints:

   ```
   Thread 2 trying to acquire mutex
   ```
2. It then **calls `mutex.lock()`**.
3. But **`thread1` already owns the mutex** and is locking/unlocking it rapidly in a loop.
4. Because **`thread1` reacquires the mutex almost instantly after releasing it**, `thread2` **never succeeds** in acquiring it.
5. So `thread2` remains **stuck inside `mutex.lock()`** forever — and **doesn't continue to the next loop iteration**.
6. Therefore, `"Thread 2 trying to acquire mutex"` is printed **only once** — before it gets blocked.


### ✅ A more verbose version of starvation

Use **`std::try_lock()`**, which is **non-blocking**:

```cpp
void thread2() {
    while (true) {
        std::cout << "Thread 2 trying to acquire mutex" << std::endl;

        if (mutex.try_lock()) {
            std::cout << "Thread 2 acquired mutex" << std::endl;
            mutex.unlock();
        } else {
            std::cout << "Thread 2 failed to acquire mutex" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
```

Now you'll see:

```
Thread 2 trying to acquire mutex
Thread 2 failed to acquire mutex
Thread 2 trying to acquire mutex
Thread 2 failed to acquire mutex
...
```


## ✅ How to Fix It?

To prevent starvation:

* **Use fair locks** (some mutex implementations support fairness).
* **Introduce sleep/yield in thread1**, allowing thread2 a fair chance:

    ```cpp
    std::this_thread::yield(); // inside thread1 loop
    ```
    
    or introduce a small pause in `thread1` after unlock:

    ```cpp
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ```
* **Use condition variables or priority-aware scheduling**, if needed.


## 🔄 Why thread2 doesn't ever get a chance after thread1 unlocks

Short Answer: It’s About Scheduling, Timing, and Mutex Implementation. Let’s break it down:

### 🧠 1. **Thread Scheduling Is Not Fair or Predictable**

The **operating system's thread scheduler** controls **which thread runs next**, and:

* It's **not guaranteed** to schedule `thread2` immediately after `thread1` unlocks.
* `thread1` finishes sleeping, unlocks, and **goes right back to locking** the mutex before the OS has a chance to schedule `thread2`.

Even if both threads are of equal priority, `thread1` is in a **tight loop** with no pause, and **usually remains “hot” in the CPU scheduler**. This gives it an unfair advantage.

---

### 🧰 2. **`std::mutex` Is Not Fair**

Most `std::mutex` implementations (e.g., on Linux with pthreads) are **not fair**:

* When the mutex is unlocked, **the OS doesn’t guarantee** the longest-waiting thread gets it.
* Instead, whichever thread tries to lock **first after unlock** wins — and if `thread1` loops fast, it usually wins.

---

### 🧵 3. **Thread 2 Is Often Asleep**

Remember: `thread2` sleeps for **500ms** after each attempt (in your code). So even if `thread2` wakes up and gets ready to run, **it loses the race** to reacquire the mutex unless it gets **extremely lucky**.

---

### ⏱ 4. **Timing Gaps Are Extremely Small**

Even when `thread1` unlocks the mutex, the **gap between unlock and re-lock is often microseconds or nanoseconds**.

Unless:

* The thread is preempted by the OS,
* Or you explicitly yield/sleep,

…it will **just keep running**.

Without intervention, `thread2` **never gets CPU time** at the right moment.

---

## 🛠 Example Fix: Yield in `thread1`

You can force `thread1` to step aside after unlocking:

```cpp
mutex.unlock();
std::this_thread::yield(); // Hint to OS: schedule someone else
```

Now you might see:

```
Thread 2 trying to acquire mutex
Thread 2 acquired mutex
```

This lets `thread2` grab the mutex **before `thread1` tries again**.

## 🔚 Summary

* `std::mutex::lock()` is blocking — once `thread2` calls it, it **stops** there until it gets the lock.
* If `thread1` keeps taking the lock quickly, `thread2` never gets past `mutex.lock()`.
* You only see `"Thread 2 trying to acquire mutex"` once — because that’s the last line it reaches before blocking forever.
