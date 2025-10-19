// https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html

#include <coroutine>
#include <iostream>
#include <cstdlib>

struct ReturnObject2 {
  struct promise_type {
    ReturnObject2 get_return_object() {
      return {
        // Uses C++20 designated initializer syntax
        .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    void return_void() noexcept {}
  };

  std::coroutine_handle<promise_type> h_;
  operator std::coroutine_handle<promise_type>() const { return h_; }
  // A coroutine_handle<promise_type> converts to coroutine_handle<>
  operator std::coroutine_handle<>() const { return h_; }
};

ReturnObject2
counter()
{
  for (unsigned i = 0;; ++i) {
    co_await std::suspend_always{};
    std::cout << "counter: " << i << "\n";
  }
}

void
main2()
{
  std::coroutine_handle<> h = counter();
  for (int i = 0; i < 3; ++i) {
    std::cout << "In main2 function\n";
    h();
  }
  h.destroy();
}

int main() {
    main2();
    return EXIT_SUCCESS;
}


/*
#include <coroutine>
#include <iostream>

struct Counter {  // ← Just the return type name!
  struct promise_type {
    Counter get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
  };
};

Counter counter() {  // Return type = Counter
  for (unsigned i = 0;; ++i) {
    co_await std::suspend_always{};
    std::cout << "counter: " << i << "\n";
  }
}

int main() {
  auto h = counter();  // Gets coroutine_handle automatically
  for (int i = 0; i < 3; ++i) {
    std::cout << "In main\n";
    h();  // Resume
  }
  h.destroy();
}
*/


/*
#include <coroutine>
#include <iostream>

struct Counter {};

Counter counter() {
  for (unsigned i = 0;; ++i) {
    co_await std::suspend_always{};
    std::cout << "counter: " << i << "\n";
  }
}

int main() {
  auto h = counter();  // Gets coroutine_handle automatically
  for (int i = 0; i < 3; ++i) {
    std::cout << "In main\n";
    h();  // Resume
  }
  h.destroy();
}
*/
