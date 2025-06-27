#include <iostream>
#include <thread>
#include <vector>

int main() {
    auto lambda = [](int i){
        std::cout << "Hello from jthread " << std::this_thread::get_id() << std::endl;
        std::cout << "Argument: " << i << std::endl;
    };
    
    std::vector<std::jthread> jthreads;
    for (int i = 0; i < 10; i++) {
        jthreads.push_back(std::jthread(lambda, i));
    }

    std::cout << "Hello from main thread" << std::endl;
    return 0;
}