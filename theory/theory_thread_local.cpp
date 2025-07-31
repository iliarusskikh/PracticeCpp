/*
 The thread_local Storage Class is the new storage class that was added in C++11. We can use the thread_local storage class specifier to define the object as thread_local. The thread_local variable can be combined with other storage specifiers like static or extern and the properties of the thread_local object changes accordingly.

 Properties of thread_local Storage Class

 Memory Location: RAM
 Lifetime: Till the end of its thread
 */

#include <iostream>
#include <mutex>
#include <thread>

// Defining thread-local variable
thread_local int val = 10;

// Mutex for synchronization
std::mutex mtx;

int main() {
  
    std::thread th4([](){
        //new function to run!
    });
    // Created 3 threads
    // Modify value in thread 1
    std::thread th1([]() {
        val += 18;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread 1 value: " << val << '\n';
    });

    std::thread th2([]() {
      
        // Modify value in thread 2
        val += 7;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread 2 value: " << val << '\n';
    });

    std::thread th3([]() {
      
        // Modify value in thread 3
        val += 13;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread 3 value: " << val << '\n';
    });

    // Wait for all threads to finish
    th1.join();
    th2.join();
    th3.join();

    // Print the value of value in the main thread
    std::cout << "Main thread value: " << val << '\n';

    return 0;
}

