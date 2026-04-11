#include <iostream>

class A {
public:
  virtual void f() { std::cout << "A"; }
};

class B : public A {
private:
  void f() { std::cout << "B"; }
};

void g(A &a) { a.f(); }

int main() {
  B b;
  g(b);
}
// Output: B
//The call point here being a.f(), and the type of the expression is A&.
