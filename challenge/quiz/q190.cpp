#include <iostream>

struct A {
  A(int i) : m_i(i) {}
  operator bool() const { return m_i > 0; }
  int m_i;
};

int main() {
  A a1(1), a2(2);
  std::cout << a1 + a2 << (a1 == a2);
}
// Output: 21
//1 + 1 equals 2, and 1 == 1 is true, so 21 is printed.


