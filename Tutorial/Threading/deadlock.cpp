#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;
static int shared_value = 0;

void increment_shared_value() {
    std::lock_guard<std::mutex> guard(gLock);
    try
    {
        shared_value += 1;
        throw "dangerous... abort"; 
    }
    catch(...)
    {
        std::cout << "handle exception\n";
        return;
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; ++i) {
        threads.push_back(std::thread(increment_shared_value));
    }

    for (auto& t : threads) t.join();

    std::cout << "Final shared value: " << shared_value << std::endl;
    return 0;
}