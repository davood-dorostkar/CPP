# Atomic

## **What is an Atomic Operation?**  
An **atomic operation** is an operation that **completes in a single step** without the possibility of being interrupted. In other words, once an atomic operation starts, it runs to completion without interference from other threads or processes.

---

## **Key Characteristics of Atomic Operations**
1. **Indivisibility:** The operation cannot be split into smaller parts. It either happens entirely or not at all.  
2. **No Interruption:** No other thread or process can observe the operation in an incomplete state.  
3. **No Race Conditions:** Since atomic operations execute fully without interruption, they prevent race conditions in multithreading scenarios.  

---

## **Examples of Atomic and Non-Atomic Operations**
### **1. Atomic Operations (Indivisible)**
- Reading a `bool`, `int`, or `char` from memory (on most architectures)
- Writing a `bool`, `int`, or `char` to memory (on most architectures)
- `std::atomic` operations in C++ (`std::atomic<int> counter; counter++;`)
- **CPU-supported atomic instructions**, like `LOCK XADD` in x86 assembly

### **2. Non-Atomic Operations (Can Be Interrupted)**
- `counter++` (Incrementing a variable)  
  - This is **not atomic** because it consists of three steps:
    1. Read the value from memory  
    2. Increment the value  
    3. Write it back to memory  
  - If two threads execute `counter++` simultaneously, a **race condition** may occur.

- Writing multiple bytes at once (e.g., modifying a `double` or `struct` on some architectures)
- Updating a linked list or modifying a data structure involving multiple memory locations

---

## **Atomic Operations in C and C++**
C++ provides `std::atomic` for atomic operations:

```cpp
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> counter(0);  // Atomic variable

void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++;  // Atomic increment
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter.load() << std::endl;
    return 0;
}
```
✅ **Output (Correct, No Race Condition):**
```
Final counter value: 200000
```

If `counter` were **not atomic**, a race condition would cause unpredictable results.

---

## **Atomicity in Low-Level Systems**
At the CPU level, atomicity is often provided using **special atomic instructions** like:
- **x86:** `LOCK CMPXCHG`, `LOCK XADD`
- **ARM:** Load-Exclusive and Store-Exclusive (`LDREX/STREX`)
- **RISC-V:** Atomic Load-Store Instructions

These ensure that certain operations occur **without interruption**.

---

## **Conclusion**
- **Atomic operations** are **indivisible** and **prevent race conditions**.  
- Use **`std::atomic`** in C++ to ensure safe multi-threaded access.  
- Some operations (like `counter++`) are **not atomic by default** and must be explicitly made atomic.  
- CPUs provide **hardware-level atomic instructions** for efficiency.
