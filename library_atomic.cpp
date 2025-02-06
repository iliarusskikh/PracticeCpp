#include <iostream>
#include <atomic>
#include <thread>

//atomic ref allows working with regular variables as if its atomic
//without copying
//useful when not using mutex

// Driver Code
int main()
{
    int shared_value = 0;
    std::atomic_ref<int> ref(shared_value);//wrap it into atomic

    auto increment_task =[&]()
    {
        for(int i = 0; i<1000;++i)
        {
            ref.fetch_add(1, std::memory_order_relaxed);
        }
    };
    
    std::thread t1(increment_task);
    std::thread t2(increment_task);
    
    t1.join();
    t2.join();
    
    std::cout<<"output sumup "<<shared_value<<"\n";
    
    return 0;
}
