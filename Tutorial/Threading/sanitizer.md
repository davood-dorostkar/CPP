# Detecting Data Races with Thread Sanitizers

Multithreading allows you to run multiple tasks in parallel — but it also introduces the risk of **data races**, where multiple threads access shared data simultaneously without proper synchronization. This can lead to **unpredictable bugs**.


## 🔁 Problem Setup: A Data Race

Here’s a simple C++ program with a **shared variable** modified by 1000 threads:

```cpp
#include <iostream>
#include <thread>
#include <vector>

static int shared_value = 0;

void shared_value_increment() {
    shared_value = shared_value + 1;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; i++) {
        threads.push_back(std::thread(shared_value_increment));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Shared value: " << shared_value << std::endl;
    return 0;
}
```

### ❗ Problem:

This program contains a **data race** — all threads are updating `shared_value` without a lock. The output is **non-deterministic** and incorrect.


## 🧪 Step 1: Compile with Thread Sanitizer

### 🧵 GCC:

```bash
g++ -std=c++17 -fsanitize=thread sanitizer.cpp -o sanitizer -lpthread
```

### 🧵 Clang:

```bash
clang++ -std=c++17 -fsanitize=thread sanitizer.cpp -o sanitizer -lpthread
```

This enables the **Thread Sanitizer**, which instruments your program to detect unsafe memory accesses between threads.


## ▶️ Step 2: Run the Program

```bash
./sanitizer
```

### 🧨 Output:

You’ll see something like this:

```
WARNING: ThreadSanitizer: data race (pid=...)
  Write of size 4 at 0x... by thread T1:
    #0 shared_value_increment() ...
  Previous write of size 4 at 0x... by thread T2:
    #0 shared_value_increment() ...
...
SUMMARY: ThreadSanitizer: data race ...
```

### 💡 What it means:

* Multiple threads are **writing** to `shared_value` **concurrently**.
* No locks are used to protect the critical section.


## 🛠️ Fix the Data Race

To fix this, **protect access to `shared_value`** using a mutex:

```cpp
std::mutex mtx;

void shared_value_increment() {
    std::lock_guard<std::mutex> lock(mtx);
    shared_value += 1;
}
```

Recompile and rerun — the sanitizer should report no data races now.


## 🧠 Pro Tips

* Use `-g` to include debug info for clearer error messages.
* Integrate sanitizers in your CI or testing scripts.
* Data races are **hard to catch manually** — let tools help you.


## ✅ Conclusion

Thread sanitizers can **save hours** of debugging by catching subtle race conditions early. Use them during development and testing!

👍 If you want to go further, look into:

* `-fsanitize=address`
* `std::atomic` for lock-free synchronization
* Memory models and the C++11 threading library

