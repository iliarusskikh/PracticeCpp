#include <iostream>

void foo(int *arr) {
  std::cout << 1 << std::endl;
}

void foo(int (&arr)[2]) {
  std::cout << 2 << std::endl;
}

int main() {
  int a[2];
  foo(a);
}

// Output: The program is ill-formed because the call to foo is ambiguous.
//Compiler error

