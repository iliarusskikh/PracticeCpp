#include <iostream>

int main() {
  int a = 0;
  decltype(a) b = a;
  b++;
  std::cout << a << b;
}
// Output: 01
//The type of a is int, so the type of b is also int.


