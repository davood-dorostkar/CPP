# Semaphores

A **semaphore** is a **synchronization primitive** used to control **access to a shared resource** by multiple threads.

**Two Main Types:**

* **Counting Semaphore**: Allows a fixed number of threads to access a resource.
* **Binary Semaphore** (like a mutex): Only 0 or 1 allowed — mutual exclusion.

## 🚀 Use Cases

* Limit access to a pool of resources (e.g., database connections)
* Coordinate producer-consumer systems
* Rate-limit access to APIs or hardware

## ✅ C++20 `std::counting_semaphore`

Since **C++20**, the Standard Library includes semaphores in `<semaphore>`.

### 📦 Example: 3 Threads Allowed at Once

```cpp
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

// Allow 3 threads to enter critical section
std::counting_semaphore<3> sem(3);  // Initial count = 3

void task(int id) {
    std::cout << "Thread " << id << " waiting to enter...\n";
    sem.acquire(); // ↓ Decrease count, block if 0
    std::cout << "Thread " << id << " entered critical section\n";

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work

    std::cout << "Thread " << id << " leaving critical section\n";
    sem.release(); // ↑ Increase count, allow another to enter
}

int main() {
    std::vector<std::thread> threads;

    // Launch 6 threads
    for (int i = 1; i <= 6; ++i) {
        threads.emplace_back(task, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

### 🧾 Expected Output

(Only 3 threads run in the critical section at a time)

```
Thread 1 waiting to enter...
Thread 1 entered critical section
Thread 2 waiting to enter...
Thread 2 entered critical section
Thread 3 waiting to enter...
Thread 3 entered critical section
Thread 4 waiting to enter...
Thread 5 waiting to enter...
Thread 6 waiting to enter...
Thread 1 leaving critical section
Thread 4 entered critical section
...
```

## ✅ Pre-C++20 Option1: 
**Use `std::mutex + std::condition_variable` to Simulate a Semaphore**

### 🧱 Custom `Semaphore` Class

```cpp
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    explicit Semaphore(int count = 0)
        : count_(count) {}

    // Decrement the counter (block if zero)
    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [&]() { return count_ > 0; });
        --count_;
    }

    // Increment the counter (unblock one waiting thread)
    void release() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        cv_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};
```

### 🧪 Example: 3 Threads Allowed at Once

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// Use our custom semaphore
Semaphore sem(3);  // Allow 3 threads in at a time

void task(int id) {
    std::cout << "Thread " << id << " waiting to enter...\n";
    sem.acquire();
    std::cout << "Thread " << id << " entered critical section\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    std::cout << "Thread " << id << " leaving critical section\n";
    sem.release();
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 6; ++i) {
        threads.emplace_back(task, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

## ✅ Pre-C++20 Option2: 
**use POSIX semaphores (`<semaphore.h>`)**

Let me walk you through this version of the **Semaphore Tutorial for C++11 with POSIX semaphores**, using your code.

`<semaphore.h>` is a POSIX-compliant way to use semaphores in C++ (usually on Linux or macOS). It works fine with **C++11** threads (`std::thread`) even though the semaphore is from C.

### 🔧 Code Example

```cpp
#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;
sem_t semaphore;

void threadFunction1()
{
    sem_wait(&semaphore);
    // decrement semaphore
    cout << "Thread 1 acquired the semaphore" << endl; 
    this_thread::sleep_for(chrono::seconds(1));
    sem_post(&semaphore); // increment semaphore
    cout << "Thread 1 released the semaphore" << endl;
}

void threadFunction2()
{
    sem_wait(&semaphore);
    // decrement semaphore
    cout << "Thread 2 acquired the semaphore" << endl;
    sem_post(&semaphore);
    // increment semaphore
    cout << "Thread 2 released the semaphore" << endl;
}

int main()
{
    sem_init(&semaphore, 0, 1); // initialize semaphore with initial value 1
    thread t1(threadFunction1);
    thread t2(threadFunction2);
    t1.join();
    t2.join();
    sem_destroy(&semaphore); // destroy semaphore
    return 0;
}
```

> Only one thread can be in the "critical section" at a time — thanks to the **binary semaphore (value = 1)**.


## API Summary
### C++20 Semaphore

| Concept     | Purpose                                     |
| ----------- | ------------------------------------------- |
| `acquire()` | Wait (decrement), blocks if count == 0      |
| `release()` | Signal (increment), unblocks waiting thread |
| Use case    | Limit concurrent access, like a gate        |

### POSIX Semaphore

| Function      | Description                |
| ------------- | -------------------------- |
| `sem_init`    | Initialize semaphore       |
| `sem_wait`    | Wait (block if value is 0) |
| `sem_post`    | Signal (increment value)   |
| `sem_destroy` | Destroy the semaphore      |

