#include <iostream>
#include <limits>

int main() {
  unsigned int i = std::numeric_limits<unsigned int>::max();
  std::cout << ++i;
}

// Output:0
//Unsigned integers have well-defined behaviour when they overflow. When you go one above the largest representable unsigned int, you end up back at zero.
