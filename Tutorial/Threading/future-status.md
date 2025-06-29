# Real-World Async Example with `std::future_status` 

This lesson builds on the basics of `std::async`, showing how to:

* Use it to load data **in the background**.
* **Continuously check** (non-blocking) whether that background task is done using `std::future_status`.
* Simulate **real-world scenarios** like loading assets in games or buffering videos.

The main idea: Let the main program continue running while another thread does heavy work in the background—only interrupt the flow once the result is ready.

---

## 📘 Tutorial: Asynchronous File Loading Simulation

### 🔧 Code

```cpp
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Simulated background task
bool bufferedFileLoader()
{
    size_t bytesLoaded = 0;
    while(bytesLoaded < 20000)
    {
        std::cout << "thread: loading file..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Simulate latency
        bytesLoaded += 1000;
    }
    return true;
}

int main(){
    // 🔹 Start background task asynchronously
    std::future<bool> backgroundThread = std::async(std::launch::async, bufferedFileLoader);

    std::future_status status;

    // 🔹 Main program loop runs in parallel
    while(true)
    {
        std::cout << "Main thread is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulated frame/update cycle

        // 🔹 Non-blocking check if background task is done
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));

        if(status == std::future_status::ready)
        {
            std::cout << "Our data is ready..." << std::endl;
            break;
        }
    }

    std::cout << "Program is complete" << std::endl;
    return 0;
}
```
**execute**:
```bash
g++ -std=c++17 -lpthread future-status.cpp -o future-status && ./future-status && rm future-status
```


### ✅ Key Concepts Recap

| Concept                               | Explanation                                                          |
| ------------------------------------- | -------------------------------------------------------------------- |
| `std::async(std::launch::async, ...)` | Launches a task immediately on a new thread                          |
| `std::future<bool>`                   | Holds the result from the background thread (here: success = `true`) |
| `wait_for(duration)`                  | Non-blocking check to see if the result is ready                     |
| `std::future_status::ready`           | Indicates that the background task has completed                     |

---

### 🧠 How It Works

1. `bufferedFileLoader()` simulates loading a large file (20,000 bytes) in chunks.
2. `std::async` launches this task on a new thread.
3. Meanwhile, the **main loop runs continuously**, representing an active game loop or UI thread.
4. On each cycle, the program uses `wait_for()` to check if the background loading is finished.
5. Once the file is "loaded", the program breaks out of the loop.


✅ **Efficient & responsive design**: The main thread stays active and responsive while waiting in parallel for heavy tasks to finish.


## Implementation Details
Great questions! These are **key points** when understanding how `std::async`, `std::future`, and `std::future_status` work together in C++. Let's walk through them one by one and clarify everything:

### ✅ 1. Why use async policy?

```cpp
std::future<bool> backgroundThread = std::async(std::launch::async, bufferedFileLoader);
```

instead of:

```cpp
std::future<bool> backgroundThread = std::async(bufferedFileLoader);
```

#### 📌 Difference:

* Without launch policy:

  ```cpp
  std::async(bufferedFileLoader);
  ```

  The launch policy is **unspecified** — it may **run immediately in a new thread** or may **defer execution** (run **only when you call `.get()`**). This behavior is **implementation-defined**, meaning it can vary between compilers.

* With launch policy:

  ```cpp
  std::async(std::launch::async, bufferedFileLoader);
  ```

  You **force** it to run **asynchronously** in a **new thread immediately**.

---

### ✅ 2. Why do we use:

```cpp
status = backgroundThread.wait_for(std::chrono::milliseconds(1));
```

instead of checking the result directly?

### 📌 Explanation:

* If you call:

  ```cpp
  backgroundThread.get();
  ```

  This **blocks** the current thread **until the result is ready**.

* But we want to **keep our main loop running** and **check periodically** whether the background task is done. That’s why we use:

  ```cpp
  backgroundThread.wait_for(std::chrono::milliseconds(1));
  ```

  This waits **at most 1 ms**, then returns a `std::future_status` enum:

  * `std::future_status::ready` → Result is available now.
  * `std::future_status::timeout` → Not ready yet.
  * `std::future_status::deferred` → The task hasn't started yet (only possible if you used `std::launch::deferred`).

So this gives us a **non-blocking way to check**: “Is the background work done yet?”

---

### 🔁 In contrast

If you didn’t care about checking and just wanted the result when needed:

```cpp
bool result = backgroundThread.get(); // Blocks until ready
```

But in real-time systems (e.g. games), **you don’t want to block** the main loop — so `wait_for()` is the right tool.

---

### 🔍 Launch Policy: `std::launch::async` vs `std::launch::deferred`

You explicitly used `std::launch::async` to **immediately** run the task in a new thread.

Alternative:

* `std::launch::deferred` delays execution until `.get()` or `.wait()` is called.

---

### 💡 Real-World Applications

* Background asset loading in games
* Video buffering (like the YouTube example)
* File I/O while maintaining responsive UI
* Network requests behind the scenes
