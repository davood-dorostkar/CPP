#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;

void thread1() {
    while (true) {
        mutex.lock();
        std::cout << "Thread 1 acquired mutex" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mutex.unlock();
        // std::this_thread::sleep_for(std::chrono::milliseconds(10)); // add a fair chance
    }
}

void thread2() {
    while (true) {
        std::cout << "Thread 2 trying to acquire mutex" << std::endl;
        mutex.lock();
        std::cout << "Thread 2 acquired mutex" << std::endl;
        mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void thread2_verbose() {
    while (true) {
        std::cout << "Thread 2 trying to acquire mutex" << std::endl;

        if (mutex.try_lock()) {
            std::cout << "Thread 2 acquired mutex" << std::endl;
            mutex.unlock();
        } else {
            std::cout << "Thread 2 failed to acquire mutex" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

 return 0;
}
