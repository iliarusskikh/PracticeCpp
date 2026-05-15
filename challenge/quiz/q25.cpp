
#include <iostream>
#include <limits>

int main() {
  int i = std::numeric_limits<int>::max();
  std::cout << ++i;
}
// Output: Signed integer overflow is undefined behaviour
//Most implementations will just wrap around, so if you try it out on your machine, you will probably see the same as if you had done
//std::cout << std::numeric_limits<int>::min();
//-2147483648
