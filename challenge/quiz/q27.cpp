#include <iostream>

struct A {
  virtual std::ostream &put(std::ostream &o) const {
    return o << 'A';
  }
};

struct B : A {
  virtual std::ostream &put(std::ostream &o) const {
    return o << 'B';
  }
};

std::ostream &operator<<(std::ostream &o, const A &a) { //operator<<(std::cout, static_cast<const A&>(b));

  return a.put(o); //virtual method, hence since pointing to b object,it prints B
}

int main() {
  B b;
  std::cout << b;
}
// Output: B
// This is a way to get polymorphic behaviour for operator <<.
