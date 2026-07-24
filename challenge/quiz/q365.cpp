#include <iostream>

int main() {
  unsigned short zero = 0, one = 1;
  if (zero - one < zero)
    std::cout << "less";
  else
    std::cout << "more";
}
// Output: unspecified
//The usual arithmetic conversion promotes integral types of conversion rank lower than int to int if int can represent all the values of the source type, and otherwise to unsigned int.
//In this case, the result of the operation is -1 with type int, and less is printed.

//If short and int have the same size, unsigned short instead gets converted to an unsigned int, the result wraps around to a large value, and more is printed.


