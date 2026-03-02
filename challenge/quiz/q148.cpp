#include <iostream>

volatile int a;

int main() {
  std::cout << (a + a);
}

//undefined behaviour
//The issue here is not the missing initializer of the variable a - it will implicitly be initialized to 0 since it has static storage duration. The issue is rather that the two accesses of a in the expression a + a are not sequenced, which leads to undefined behavior.
