#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include <queue>
#include <conditional_variable>//synchronisation primitives that enable threads to wait until a specific condition occurs

#include <future>
#include <chrono>

#include <atomic>

#include <algorithm>
#include <execution>
#include <random>


int co = 0;
std::mutex mtx;

std::mutex mutex1, mutex2;


std::atomic<int> county{0};

int counter = 0;
std::mutex counter_mutex; //protects counter

void process_data(int id){
    std::cout <<"Thread " <<id <<" Working" << std::endl;
}



void increment(int iterations){
    for(int i=0; i< iterations; ++i){
        std::lock_guard<std::mutex>lock(counter_mutex); //safer use of mutexes using RAII (Resource acquisition is initialisation wrapper - automatically locks and unlocks when destroyed object
        counter++;//now protected by mutex
    }
}


std::queue<int>data_queue;
std::mutex queue_mutex;
std::conditional_variable cv;
bool done = false;

void producer() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            data_queue.push(i);
            std::cout << "[Producer] pushed " << i << "  (queue size = "
                      << data_queue.size() << ")\n";
        }
        
        // Notify consumer after each push
        cv.notify_one();

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    // Final notification: no more data
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        done = true;
    }
    cv.notify_one();   // Important: wake consumer even if queue is empty
    std::cout << "[Producer] finished → sent done signal\n";
}
//wait - block until notified and condition is true
//notify_all - wake up all waiting threads
void consumer() {
    while (true) {
        int value;

        {
            // Use unique_lock because we need to wait (lock_guard can't wait)
            //also you can manually unlock and lock it back
            std::unique_lock<std::mutex> lock(queue_mutex);

            // Wait until: queue not empty OR done == true
            cv.wait(lock, [&] {
                return !data_queue.empty() || done;
            });

            // If queue is empty and we're done → exit loop
            if (data_queue.empty() && done) {
                std::cout << "[Consumer] queue empty + done → exiting\n";
                break;
            }

            // Safe to pop now
            value = data_queue.front();
            data_queue.pop();

            std::cout << "[Consumer] consumed " << value
                      << "  (queue size now = " << data_queue.size() << ")\n";
        }

        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}





//std::future represents a value that will be available in the future
//std::promise sets the value for an associated future
//std::async runs a function asynchronously and returns a future
//std::packaged_task wraps a callable object to store its result
int compute_value(){
    //simulate long task
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 21;
}




//atomic
void incr(int iter){
    for(int i; i< iter; ++i){
        county; //no mutex needed for atomic
    }
}




void safe_in(){
    mtx.lock();
    co++;
    mtx.unlock();
}



//locking multiple mutexes safely
void no_deadlock_operation(){
    std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);
    
    //lockboth mutexes without deadlock
    std::lock(lock1,lock2);
    //now bock mutexes are locked
    
    
    //alternatively with C++17
    std::scoped_lock lock(mutex1, mutex2); //all mutexes are locked, automatically unlocking when lock goes out of scope
    
}


int main()
{
    std::vector<std::thread>threads;
    
    for(int i = 0; i < 4; ++i){
        threads.emplace_back(process_data,i);//i for id
    }
    
    for(auto& t: threads){
        t.join();//wait for each to complete before the program exits
    }
    
    //.join() wait for completion
    //.detach() - run independently
    //.get_id() unique identifier
    //joinable() - check if a thread can be joined
    
    
    //mutex to prevent race conditions
    std::thread t1(increment, 1000);
    std::thread t2(increment, 1000);
    t1.join();
    t1.join();
    
    
    std::cout << counter <<std::endl;
    
    //condition variables
    
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();


    
    
    //futures and promises
    std::future<int> result = std::async(std::launch::async. compute_value);
    //do other work while computation happens
    //do work
    std::cout << "Result "<<result.get() << std::endl;
    
    
    //atomic operations
    
    t1(incr, 1000);
    t2(incr, 1000);
    t1.join();
    t1.join();
    
    
    //parallel algorithms C++17
    std::vector<int> v(100000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,1000);
    
    std::generate(v.begin(),v.end(),[&](){return dist(gen);});
    //sort in parallel
    std::sort(std::execution::par, v.begin(), v.end());
    
    
    
    
    
    
    
    //thread synchronisation
    
    
    
    
    
    return EXIT_SUCCESS;
}
