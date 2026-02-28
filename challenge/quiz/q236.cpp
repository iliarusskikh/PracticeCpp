#include <iostream>

struct Foo {
  operator auto() {//Return type deduced from return
    std::cout << "A";
    return 1;
  }
};

int main() {
  int a = Foo();
    // Step 1: Foo() creates temporary
    // Step 2: operator auto() called → prints "A", returns 1
    // Step 3: 1 converted to int a
  std::cout << a; // Step 4: prints "1"
}
// A1
