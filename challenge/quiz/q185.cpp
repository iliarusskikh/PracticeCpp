#include <iostream>

template <typename T> void f() {
  static int stat = 0;
  std::cout << stat++;
}

int main() {
  f<int>();
  f<int>();
  f<const int>();
}
// Output: 010
//The functions called by f<int>() and f<const int>() actually have the same function type, but they are still distinct functions, so each get their own distinct static int stat.
