//c++17, shared_mutex allows shared and unique lock
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex mutvar;

int shared_data = 0;

void reader(int id)
{
    std::shared_lock lock(mutvar); //few threads can read this
    std::cout << "Reader" << id <<"here" << std::endl;
}

void writer(int id)
{
    std::unique_lock lock(mutvar); //only one thread can read this
    shared_data += 10;
    
    std::cout << "Updated value" << id <<"here " << shared_data<< std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0 ; i<3 ; ++i)
    {
        threads.emplace_back(reader,i);
    }
    
    threads.emplace_back(writer,1);
    threads.emplace_back(reader,4);
    
    for(auto&t : threads)
    {
        t.join();
    }
    
    return 0;
}
