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