#include <iostream>

struct A {
  A() { foo(); }
  virtual ~A() { foo(); }
  virtual void foo() { std::cout << "1"; }
  void bar() { foo(); }
};

struct B : public A {
  virtual void foo() { std::cout << "2"; }
};

int main() {
  B b;
  b.bar();
}
// Output: 121
//1 During base class construction, virtual functions resolve to the base class version (A::foo()).
//2 Inside bar(), foo() is called virtually. The object is now fully constructed (B), so it calls B::foo().
//1 During base class destruction, virtual functions again resolve to the base class. A::foo()
