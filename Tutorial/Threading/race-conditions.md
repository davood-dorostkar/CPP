# 🧠 Race Condition

A **race condition** happens when:

* Two or more threads access **shared state**,
* At least one of them **writes**,
* And the final outcome depends on the **timing or order of execution**.

Types of Race Conditions are:

## 1. 🔁 **Thread Interference**

> Two threads modify shared data without synchronization.

**Example**:

```cpp
counter++; // Not atomic → leads to corruption
```

This is the most basic and common form.



## 2. 🧮 **Check-Then-Act Race**

> A thread **checks** a condition and **acts** on it, but another thread changes the condition **in between**.

**Example**:

```cpp
if (!file_exists("data.txt")) {
    create_file("data.txt"); // Race if another thread creates it here
}
```

Used in file systems, caches, flags.



## 3. 🔒 **Time-of-Check to Time-of-Use (TOCTOU)**

> A subtype of check-then-act, often in **security bugs**.

**Example (Linux):**

```cpp
if (access("file", W_OK) == 0) {
    // Safe to open?
    int fd = open("file", O_WRONLY); // File could have changed in between
}
```

**Common in:** OS-level code, security vulnerabilities, resource permissions.



## 4. 🧵 **Initialization Races**

> Two threads try to **initialize** a shared resource at the same time.

**Example**:

```cpp
if (ptr == nullptr) {
    ptr = new Object(); // Two threads might run this at once
}
```

Use **`std::call_once`** or **double-checked locking with mutex** to prevent this.



## 5. 🔁 **Lost Update**

> Two threads **read-modify-write** the same variable, and one update is lost.

**Example**:

```cpp
// Thread 1 reads x = 5
x = x + 1; // x = 6

// Thread 2 reads x = 5
x = x + 2; // x = 7 → Overwrites thread 1
```

Final result should be 8, but ends up 6 or 7.



## 6. 💥 **Non-Atomic Compound Operations**

> Similar to thread interference but more subtle. Happens in `std::vector` operations, counters, etc.

**Example**:

```cpp
if (!vec.empty()) {
    vec.pop_back(); // Unsafe without mutex
}
```



## 7. 🧠 **Memory Visibility (or Publication) Races**

> One thread writes a value to memory, but **another thread does not see the update**, due to **CPU caching** or compiler reordering.

**Example**:

```cpp
bool ready = false;
int data = 0;

Thread 1:
data = 42;
ready = true; // Might be reordered!

Thread 2:
if (ready) std::cout << data; // Might see stale data
```

Use `std::atomic`, fences, or synchronization primitives to fix.



## 8. ⚖️ **ABA Problem (Lock-Free Algorithms)**

> A thread reads a value `A`, does something, and finds the value still equals `A` — but it was actually **changed to B and back to A** in between.

**Common in:** Lock-free data structures, like stacks and queues.



## 🧾 Summary Table

| Type                    | Description                                          | Fix                                    |
| -- | - | -- |
| Thread Interference     | Concurrent writes interfere                          | Mutex / `std::atomic`                  |
| Check-Then-Act          | Condition changes after checking                     | Lock / atomic flag                     |
| TOCTOU                  | Condition changes between check and use              | OS-level synchronization               |
| Initialization Race     | Multiple threads initialize once-only resource       | `std::call_once`                       |
| Lost Update             | Updates overwrite each other                         | Mutex / atomic fetch-add               |
| Compound Operation Race | Safe-looking sequences fail without sync             | Lock or use thread-safe APIs           |
| Memory Visibility Race  | Threads don't see latest data                        | Use `std::atomic` + fences             |
| ABA Problem             | Value is modified and restored — causes logical bugs | Use tagged pointers or hazard pointers |
