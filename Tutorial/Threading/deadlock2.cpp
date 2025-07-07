#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void thread1()
{
    std::cout << "Thread 1 acquired mutex 1" << std::endl;
    mutex1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread 1 trying to acquire mutex 2" << std::endl;
    mutex2.lock();
    std::cout << "Thread 1 acquired mutex 2" << std::endl;
    mutex2.unlock();
    mutex1.unlock();
}

void thread2()
{
    std::cout << "Thread 2 acquired mutex 2" << std::endl;
    mutex2.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread 2 trying to acquire mutex 1" << std::endl;
    mutex1.lock(); std::cout << "Thread 2 acquired mutex 1" << std::endl;
    mutex1.unlock();
    mutex2.unlock();
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join(); t2.join();
    return 0;
}
