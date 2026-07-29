#include <iostream>

int main() {
  int i = 1, j = 1, k = 1;
  std::cout << ++i || ++j && ++k;
  std::cout << i << j << k;
}
// Output: 2211
//parsed as (std::cout << ++i) || (++j && ++k)

