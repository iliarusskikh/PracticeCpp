#include <iostream>

int main() {
  int a = 0;
  decltype((a)) b = a;
  b++;
  std::cout << a << b;
}

// Output: 11

//Because a is encapsulated in parentheses, it is treated as an lvalue, therefore b's type is int&, not int.
