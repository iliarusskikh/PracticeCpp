#include <iostream>

void f(int) { std::cout << "i"; }
void f(double) { std::cout << "d"; }
void f(float) { std::cout << "f"; }

int main() {
  f(1.0); // double  by default to give a better precision. If float is needed, 1.0f.
}
// Output: d
