#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::cout<<"Wait for 3 seconds:" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}

