#include <iostream>

int main() {
  int i = 42;
  int j = 1;
  std::cout << i / --j;
}
//Integer division by zero is undefined behaviour. A
