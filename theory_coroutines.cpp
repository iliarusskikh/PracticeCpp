//coroutines = async code execution which allows pausing and continuing execution without thread blocking. simpler than threads
//co_await, co)yield, co_return, std::generator, std::future, std::promise
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>

struct Awaitable {
    bool await_ready() { return false; } // Always suspend the coroutine
    void await_suspend(std::coroutine_handle<> handle) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate async work
        handle.resume(); // Resume coroutine after delay
    }
    void await_resume() {} // No result to return
};

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

Task myCoroutine() {
    std::cout << "Coroutine starts...\n";
    co_await Awaitable();  // Simulate async operation (e.g., waiting for I/O)
    std::cout << "Coroutine resumes after async work...\n";
}

int main() {
    myCoroutine();
    std::cout << "Main function continues executing while coroutine is suspended...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Ensure coroutine has time to finish
    std::cout << "Main function ends.\n";
    return 0;
}

