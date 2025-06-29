#include <iostream>
#include <future>

int square(int x){
    return x * x;
}

int main(){
    std::future<int> asyncFunction = std::async(&square, 12);

    // Do other work while async task runs
    for(int i = 0; i < 10; ++i){
        std::cout << square(i) << std::endl;
    }

    // Block only when result is needed
    int result = asyncFunction.get();

    std::cout << "result is: " << result << std::endl;
    return 0;
}