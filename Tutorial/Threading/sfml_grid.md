# C++ Multithreading Example – Visual Grid Update with SFML

In this lesson, we explore a **fun and visual example** of concurrency using modern C++ and the **SFML graphics library**. You’ll learn:

* How to launch multiple threads
* When locks are (and aren't) needed
* How threads can safely update shared data in parallel
* Real-world design considerations for multi-threaded programs

>the full code is [here](sfml_grid.cpp)

## 🧩 The Problem We're Solving

We're building a **2×2 grid of shapes**. Each shape has a color that updates every second in its own thread. While that’s happening, the **main thread** handles drawing and window events (like closing the app).

Visually, the result is a window with 4 changing-colored circles — a cool way to observe **independent concurrent updates**.


## 🧱 Project Structure Overview

install SFML library:

```bash
sudo apt install -y libsfml-dev
```

### 🔧 Compilation Command

```bash
g++ -std=c++17 sfml_grid.cpp -o sfml_grid -lpthread -lsfml-graphics -lsfml-window -lsfml-system && \\
./sfml_grid && rm sfml_grid
```


## 🧠 Key Concepts

### 1. **Thread-Safe Parallelism Without Locks**

Each thread updates **a different cell** in the grid, so **no two threads access the same memory location**. This avoids **data races** naturally.

✅ When threads operate on **disjoint memory**, you often don’t need `std::mutex`.


### 2. **Global Shared Resources**

```cpp
static std::vector<int> grid; // Shared but accessed independently
std::vector<std::unique_ptr<sf::Shape>> shapes;
bool isRunning = true; // Shared flag to stop threads
```

* `grid`: stores color states for each shape (`0 = red`, `1 = green`, etc.)
* `shapes`: holds the drawable objects (using `unique_ptr` for safe memory)
* `isRunning`: used to **gracefully signal** all threads to stop


## 🧵 Thread Logic: `update_grid`

```cpp
void update_grid(int x, int y){
    while(isRunning){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        grid[y*2 + x] = rand() % 4;
    }
}
```

Each thread:

* Sleeps 1 second
* Randomly updates the color index of its associated shape in `grid`

> 🧠 No mutex is needed because **each (x, y)** maps to a **unique index**: `grid[y*2 + x]`.


## 🧼 Initial Setup in `main`

```cpp
grid.reserve(4);
std::fill(begin(grid), end(grid), 0);
```

* Grid is **initialized with 4 entries**
* Shapes are created with `std::make_unique<sf::CircleShape>`

---

## 🚀 Thread Launch

```cpp
for(int x = 0; x < 2; x++){
    for(int y = 0; y < 2; y++){
        threads.push_back(std::thread(update_grid, x, y));
    }
}
```

> ✅ Uses the correct thread creation syntax:

```cpp
threads.push_back(std::thread(update_grid, x, y));
```

> Each thread operates on a different `(x, y)` position — data parallelism at its finest!

---

## 🖼 Main Game Loop

```cpp
while (window.isOpen() && isRunning) {
    // 1. Handle user events
    // 2. Clear window
    // 3. Update shape positions and colors from grid
    // 4. Draw everything
}
```

This is the **UI/rendering thread**. While threads update the grid in the background, the main loop:

* Reads from `grid`
* Updates shape colors
* Draws the current frame

---

## 🛑 Graceful Shutdown

```cpp
for (auto& th : threads) {
    th.join();
}
```

Before the app exits, the main thread **joins all threads**, ensuring they finish cleanly.


## 🧠 Concurrency Lessons from the Example

### ✅ When Locks Aren’t Needed

* If threads never access the same memory (`grid[y*2 + x]` is unique for each `(x, y)`), **you don’t need locks**.

### ❌ When Locks Would Be Needed

* If multiple threads were to write to the **same element** or shared structure (e.g., shapes vector), you'd need `std::mutex`.

---

## 🧠 Design Discussion

* The program uses **worker threads** for background computation and a **main thread** for rendering.
* You could expand this to a larger grid or add logic where worker threads depend on each other — which may then require `mutex`, `condition_variable`, or `atomic`.


## 📌 Bonus: Suggestions for Extension

* Animate movement, not just color
* Add user interaction (e.g., click to change color)
* Expand to a bigger grid (e.g., 10×10)
* Use `std::atomic<bool> isRunning` for safety
* Use `std::jthread` in C++20 for automatic joining

## 🔚 Summary

This project is a **practical concurrency demo** showing:

✅ Launching and managing threads
✅ When synchronization is *not* necessary
✅ Sharing data across threads safely
✅ Gracefully shutting down a multi-threaded program
✅ Using SFML to visualize thread behavior

