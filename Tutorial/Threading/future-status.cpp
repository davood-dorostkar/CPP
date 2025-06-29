#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Simulated background task
bool bufferedFileLoader()
{
    size_t bytesLoaded = 0;
    while(bytesLoaded < 20000)
    {
        std::cout << "thread: loading file..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Simulate latency
        bytesLoaded += 1000;
    }
    return true;
}

int main(){
    // 🔹 Start background task asynchronously
    std::future<bool> backgroundThread = std::async(std::launch::async, bufferedFileLoader);

    std::future_status status;

    // 🔹 Main program loop runs in parallel
    while(true)
    {
        std::cout << "Main thread is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulated frame/update cycle

        // 🔹 Non-blocking check if background task is done
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));

        if(status == std::future_status::ready)
        {
            std::cout << "Our data is ready..." << std::endl;
            break;
        }
    }

    std::cout << "Program is complete" << std::endl;
    return 0;
}