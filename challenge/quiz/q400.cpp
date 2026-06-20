#include <iostream>
#include <thread>

int main() {
  int not_atomic = 0;
  not_atomic++;
  std::thread t{[&]() { not_atomic++; }};
  t.join();
  std::cout << not_atomic;
}

// Output:2

