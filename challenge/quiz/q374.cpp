#include <iostream>

struct Foo {
  Foo() {}
  Foo(int n) : Foo() { throw n; }
  ~Foo() { std::cout << "B"; }
};

int main() {
  try {
    Foo(0);
  } catch (...) {
    std::cout << "A";
  }
}


//Output: BA
//If the compound-statement of the function-body of a delegating constructor for an object exits via an exception, the object's destructor is invoked.
//Foo's destructor will be called, causing B to be printed. Next, the exception gets caught in the catch handler in main, causing A to be printed.
