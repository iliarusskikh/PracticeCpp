#include <iostream>

int main() {
  int a = 10;
  int b = 20;
  int x;
  x = (a, b);
  std::cout << x;
}
// Output :20
//The type and value of the result are the type and value of the right operand
