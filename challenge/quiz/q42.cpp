#include <initializer_list>
#include <iostream>

struct A {
  A() { std::cout << "1"; }

  A(int) { std::cout << "2"; }

  A(std::initializer_list<int>) { std::cout << "3"; }
};

int main(int argc, char *argv[]) {
  A a1;
  A a2{};
  A a3{ 1 };
  A a4{ 1, 2 };
}// Output: 1133

//Initializer list constructors are greedy, so even though A(int) constructor is available, the standard mandates that initializer_list<int> is prioritized, and if - and only if - it's not available, the compiler is allowed to look for other constructors.
