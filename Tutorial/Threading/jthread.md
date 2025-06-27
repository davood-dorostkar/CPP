# Simplify Multithreading with `std::jthread` (C++20)

In previous lessons, managing multiple threads with `std::thread` required **manually calling `.join()`** for each thread — a step that's easy to forget and can lead to program errors. C++20 introduces `std::jthread`, a safer and more modern alternative to `std::thread`, which **automatically joins** threads when they go out of scope using **RAII** (Resource Acquisition Is Initialization).

---

## `std::jthread` in Action

> You’ll need **C++20** support (`-std=c++20`) for `std::jthread`.

---

### ✅ Clean & Safe Version with `std::jthread`

```cpp
#include <iostream>
#include <thread>
#include <vector>

int main() {
    auto lambda = [](int i){
        std::cout << "Hello from jthread " << std::this_thread::get_id() << std::endl;
        std::cout << "Argument: " << i << std::endl;
    };
    
    std::vector<std::jthread> jthreads;
    for (int i = 0; i < 10; i++) {
        jthreads.push_back(std::jthread(lambda, i));
    }

    std::cout << "Hello from main thread" << std::endl;
    return 0;
}
```

🎯 Each `std::jthread` is **automatically joined** when the `jthreads` vector goes out of scope.

---

### Execution

```bash
g++ -std=c++20 -pthread jthread.cpp -o jthread && ./jthread && rm jthread
```

💡 Output might appear **messed up** due to multiple threads printing simultaneously — this is expected and shows **true concurrency**.

---

## 🛠 When to Use `std::jthread`

Use `std::jthread` **whenever you don't need manual control** over thread lifetime. It helps avoid forgetting to join threads and makes your multithreaded code cleaner and safer.

---

## 👑 Final Advice

If your compiler supports C++20, prefer `std::jthread` over `std::thread` — it’s safer, cleaner, and reduces boilerplate.