# Launching and Managing Multiple Threads in C++

## Creating and Launching Multiple Threads

Instead of writing repetitive thread creation lines, use a `std::vector<std::thread>` to store and manage them.

### ✅ Correct Version (All threads run concurrently)

```cpp
#include <iostream>
#include <thread>
#include <vector>

void worker(int id) {
    std::cout << "Hello from thread " << std::this_thread::get_id() 
              << ", argument: " << id << std::endl;
}

int main() {
    std::vector<std::thread> threads;

    // Launch 10 threads with different arguments
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(worker, i));
    }

    // Join all threads AFTER launching them
    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }

    std::cout << "Hello from main thread\n";
    return 0;
}
```

---

### ❌ Incorrect Version (Threads run sequentially, not concurrently)

```cpp
for (int i = 0; i < 10; ++i) {
    std::thread t(worker, i);
    t.join(); // blocks the main thread before next thread is launched
}
```

---

### Output Example (Note the Interleaving):

```
Hello from thread 0x7f9c0c0056c0, argument: 0
Hello from thread 0x7f9c0b8046c0, argument: 1
Hello from thread 0x7f9c0b0036c0, argument: 2
...
Hello from main thread
```

> 🧠 **Note**: Output may appear messed up because multiple threads are writing to `std::cout` simultaneously. This is **normal** and expected unless you use synchronization tools like `std::mutex`.

---

## 💡 Key Takeaways

* Use a `std::vector<std::thread>` to manage many threads dynamically.
* Always **launch all threads first**, then **join** them after.
* Output messed up due to lack of synchronization in console output.
* Use `std::this_thread::get_id()` to get the ID of the current thread.
* Compiling: use `-lpthread` on Linux.

```bash
g++ -std=c++11 multiple-threads.cpp -o multiple-threads -lpthread
```

---

## 📌 Next Step  (will be discussed later)

To **synchronize output**, wrap `std::cout` inside a mutex lock:

```cpp
std::mutex cout_mutex;

void worker(int id) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "Thread " << std::this_thread::get_id() 
              << " doing work with arg: " << id << std::endl;
}
```