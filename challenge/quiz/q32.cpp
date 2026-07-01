#include <iostream>

struct X {
  X() { std::cout << "a"; }
  X(const X &x) { std::cout << "b"; }
  const X &operator=(const X &x) {
    std::cout << "c";
    return *this;
  }
};

int main() {
  X x;
  X y(x);
  X z = y;
  z = x;
}
// Output: abbc

//So both our cases use the copy constructor.

//Not until z = x; do we have an actual assignment that uses the assignment operator.
