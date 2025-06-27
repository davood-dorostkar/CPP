#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void simpleWorker(int id) {
    std::cout << "Hello from thread " << std::this_thread::get_id() 
              << ", argument: " << id << std::endl;
}

std::mutex cout_mutex;
void safeWorker(int id) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "Hello from Thread " << std::this_thread::get_id() 
              << ", argument: " << id << std::endl;
}

void (*worker)(int id);

int main() {
    worker = simpleWorker;
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