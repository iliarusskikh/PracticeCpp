#include <iostream>
#include <string>
#include <future>

int main() {
  std::string x = "x";

  std::async(std::launch::async, [&x]() {
    x = "y";
  });
  std::async(std::launch::async, [&x]() {
    x = "z";
  });

  std::cout << x;
}
//Z
//The destructor of a future returned from async is required to block until the async task has finished (see elaboration below). Since we don't assign the futures that are returned from async() to anything, they are destroyed at the end of the full expression (at the end of the line in this case).
//This means that the first async call is guaranteed to finish execution before async() is called the second time, so, while the assignments themselves may happen in different threads, they are synchronized.
