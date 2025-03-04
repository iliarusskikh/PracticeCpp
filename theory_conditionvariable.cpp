#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_hello()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{return ready; }); //wait for ready to becoming TRUE
    std::cout << "Hello there .." <<std::endl;
}

void set_ready()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();// notify one of awaiting threads
    
}

int main()
{
    std::thread t1(print_hello);
    std::thread t2(set_ready);
    t1.join();
    t2.join();
        
    return 0;
}

