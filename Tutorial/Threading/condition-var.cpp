#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main(){
    int result = 0;
    bool notified = false;

    // 🧾 Reporting thread (waits for notification)
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified){
            gConditionVariable.wait(lock);  // Waits until notified (goes to sleep mode)
        }
        std::cout << "Reporter, result is: " << result << std::endl;
    });

    // 🔧 Working thread (does work and notifies)
    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock);
        result = 42 + 1 + 7;  // Do some computation
        notified = true;     // Update shared state
        std::this_thread::sleep_for(std::chrono::seconds(3));  
        std::cout << "Work complete\n";
        gConditionVariable.notify_one();  // Notify the waiting thread
    });

    reporter.join();
    worker.join();

    std::cout << "Program complete" << std::endl;
    return 0;
}