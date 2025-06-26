#include <iostream>
#include <atomic>
#include <thread>

int nonAtomicCounter = 0;  // Non-Atomic variable
std::atomic<int> AtomicCounter(0);  // Atomic variable

void increment() {
    for (int i = 0; i < 100000; i++) {
        nonAtomicCounter++;  // non-Atomic increment
        AtomicCounter++;  // Atomic increment
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final non-atomic counter value: " << nonAtomicCounter << std::endl;
    std::cout << "Final atomic counter value: " << AtomicCounter.load() << std::endl;
    return 0;
}