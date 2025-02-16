# Simple Thread in C++

## What is a Thread?

A thread is often referred to as a *lightweight process*. Every application has a main thread that begins execution from the main function, whether it's a single-threaded or multi-threaded application. In multi-threaded applications, each thread has its own logical flow of control, meaning it can execute functions concurrently. 

Threads share the same code base and libraries, but they may operate on different states or work with different data. Essentially, a thread is like a lightweight process, and if you're familiar with multi-process parallelism, thread-based concurrency is a similar concept but with a few differences.

## Threading in C++

In modern C++, starting from C++11, we can use the standard `thread` library to manage threads. 

There are also other threading libraries like Intel’s Threading Building Blocks (TBB), Boost’s thread library, or POSIX threads (pthreads), which you might come across, especially in Linux programming. 

I recommend using the standard thread library for better portability across platforms.

## When to Use Threads?

- We typically use threads when we have computationally intensive tasks or when we need to improve performance by parallelizing execution. Threads can help speed up processes by distributing the workload. 
- You might also use threads to simplify logic, especially when you need to manage multiple tasks that run independently but share the same program.

## C++ Thread Support

C++11 introduced the `std::thread` class as part of its standard library. Let’s take a quick look at how to use it.

```cpp
#include <iostream>
#include <thread>

void test(int x) {
    std::cout << "Hello from thread\n";
    std::cout << "Argument passed in: " << x << std::endl;
}

int main() {
    // Create a new thread
    std::thread myThread(test, 100);
    
    // Wait for the thread to finish
    myThread.join();

    std::cout << "Hello from main thread\n";

    return 0;
}
```

In this program, we create a new thread and pass an argument (`100`) to the `test` function. The `join()` call ensures that the main thread waits for `myThread` to finish before proceeding.

## Compilation and Execution

To compile the program, make sure to link the pthread library (on Linux):

```bash
g++ -std=c++17 thread_example.cpp -o thread_example -pthread
```

Running the program will produce the following output:

```
Hello from thread
Argument passed in: 100
Hello from main thread
```

## Synchronization

The key challenge with threading is synchronization. When we launch a thread, its execution is independent, and it may finish before or after the main thread. To ensure correct order, we use `join()` to make the main thread wait for the newly created thread to finish before terminating.

Without the `join()`, the main program might finish execution while the thread is still running, leading to errors like a core dump. 

## Creating a Thread with a Lambda

In the previous example, we had a `test` function that we used to run in a thread. Now, instead of defining a separate function, we’ll embed it directly in the `main` function as a lambda.

```cpp
#include <iostream>
#include <thread>

int main() {
    // Define a lambda function
    auto lambda = [](int x) {
        std::cout << "Hello from thread\n";
        std::cout << "Argument passed in: " << x << std::endl;
    };

    // Create a thread using the lambda
    std::thread myThread(lambda, 100);

    // Wait for the thread to finish
    myThread.join();

    std::cout << "Hello from main thread\n";

    return 0;
}
```

## std::thread Input

When using the `std::thread` constructor, you can pass a function pointer, a standard function, or a lambda function like we did here. It's a flexible way to define the work that a thread will perform.

## Copy vs Move Threads

**threads are non-copyable**. This means you cannot copy a thread, and you’ll see that the copy constructor for `std::thread` is deleted in the documentation. You can, however, use *move semantics* to pass threads around if necessary.