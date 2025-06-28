# `std::atomic` (C++17)

**`std::atomic`** is a thread-safe data type that allows multiple threads to **read and write shared variables** **without using locks**.

An **atomic operation** is an operation that **completes in a single step** without the possibility of being interrupted. In other words, once an atomic operation starts, it runs to completion without interference from other threads or processes.

Rather than managing `std::mutex` and `std::lock_guard` (which may be overcomplicated for simple tasks like an increment), `std::atomic` ensures that operations like `++`, `+=`, and `--` are **atomic**, meaning they happen indivisibly — without risk of **data races**.

---

## **Key Characteristics of Atomic Operations**
1. **Indivisibility:** The operation cannot be split into smaller parts. It either happens entirely or not at all.  
2. **No Interruption:** No other thread or process can observe the operation in an incomplete state.  
3. **No Race Conditions:** Since atomic operations execute fully without interruption, they prevent race conditions in multithreading scenarios.  

---

## 🧪 Tutorial: Using `std::atomic` for Thread-Safe Value Updates

### 📦 Headers Required

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
```
⚠️ It requires at least C++17.

---

### 🚫 Traditional (Unsafe) Counter with `int`

```cpp
int shared_value = 0;

void increment() {
    shared_value++;
}
```

* ❌ Risk of **data races** if multiple threads run this simultaneously.
* ❌ Needs a `mutex` to be safe.

---

### ✅ Atomic Version (Thread-Safe Without Locks)

```cpp
std::atomic<int> shared_value = 0;

void increment() {
    shared_value++;  // This is atomic and safe
}
```

### 🧵 Full Working Example 

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> shared_value = 0;

void increment_shared_value() {
    shared_value++;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; ++i)
        threads.push_back(std::thread(increment_shared_value));

    for (auto& t : threads) t.join();

    std::cout << "Final shared value: " << shared_value << std::endl;
    return 0;
}
```

#### 💡 Output (Always Deterministic):
```bash
g++ -std=c++17 atomic.cpp -o atomic && ./atomic && rm atomic
```

```
Final shared value: 1000
```

---

### ⚠️ What NOT to Do with Atomics

These expressions **are NOT safe** unless explicitly supported:

```cpp
shared_value = shared_value + 1;     // ❌ May still interleave reads/writes
shared_value += 1;                   // ✅ Actually supported in `std::atomic`
```

* ✅ Use **`++`, `--`, `+=`, `-=`**.
* ❌ Avoid raw expressions like `x = x + 1` — not atomic.

---

### 🧬 How It Works Internally

* Atomic operations typically use **hardware-supported instructions** like:

  * **Compare-and-swap**
  * **Test-and-set**
* These are very fast and allow updates without blocking other threads.

At the CPU level, atomicity is often provided with:
- **x86:** `LOCK CMPXCHG`, `LOCK XADD`
- **ARM:** Load-Exclusive and Store-Exclusive (`LDREX/STREX`)
- **RISC-V:** Atomic Load-Store Instructions

---

### 🧠 Supported Types

`std::atomic<T>` works best for **primitive types**:

* `bool`, `int`, `float`, `char`, `pointer`, etc.

It can also be used with **user-defined types** if:

* The type is trivially copyable
* It's just a collection of raw bits

🔍 Full list of overloads: [`std::atomic` on cppreference](https://en.cppreference.com/w/cpp/atomic/atomic)

---

## ✅ Final Advice

| Option                      | When to Use                                       | Pros                             | Cons                                 |
| --------------------------- | ------------------------------------------------- | -------------------------------- | ------------------------------------ |
| `std::mutex` + `lock_guard` | Complex critical sections with multiple variables | Flexible and explicit            | Risk of deadlock or forgotten unlock |
| **`std::atomic`**           | Simple single-variable updates                    | Fast, clean, no risk of deadlock | Limited to simple types              |

---

## 📌 Key Takeaways

* `std::atomic` is a **better, cleaner, safer** alternative when you just need to update a single shared value.
* It **avoids common bugs** like forgetting to unlock or overusing synchronization.
* Works **without using any manual locks** or blocking primitives.
* **Atomic operations** are **indivisible** and **prevent race conditions**.  
* Some operations (like `counter++`) are **not atomic by default** and must be explicitly made atomic.  