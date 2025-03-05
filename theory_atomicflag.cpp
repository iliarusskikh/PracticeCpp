//low level sync threads non blocking
#include <iostream>
#include <atomic>
#include <thread>

std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
//It ensures that only one thread enters the critical section at a time.
void critical_section(int id)
{
    while(lock_flag.test_and_set(std::memory_order_acquire))
    {
        //wait for releasing spinlock
    }
    std::cout << "Entered critical section.." <<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Exited critical section.." <<std::endl;
}

int main()
{
    std::thread t1(critical_section,1);
    std::thread t2(critical_section,2);
    
    t1.join();
    t2.join();
    
    return 0;
}

