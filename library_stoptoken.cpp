//alternative to std::atomic<bool> or std::condition_variable
//allows soft termination of threads without forced quit
#include<iostream>
#include<thread>
#include<chrono>
#include<stop_token>

void worker(std::stop_token stoken)
{
    while(!stoken.stop_requested())
    {
        std::cout <<"Working.." <<"\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
    
}

int main()
{
    std::jthread t(worker); //jthread automatically terminates thread
    std::this_thread::sleep_for(std::chrono::seconds(3)); //
    t.request_stop(); //request for termination
    return 0;
}

