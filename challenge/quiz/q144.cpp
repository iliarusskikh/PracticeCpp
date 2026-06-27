#include <iostream>

class A;

class B {
public:
  B() { std::cout << "B"; }
  friend B A::createB();
};

class A {
public:
  A() { std::cout << "A"; }

  B createB() { return B(); }
};

int main() {
  A a;
  B b = a.createB();
}

// Output: Compiler error:
//There is a compilation error when attempting to declare A::createB() a friend of B. To declare A::createB() a friend of B, the compiler needs to know that that function exists. Since it has only seen the declaration of A so far, not the full definition, it cannot know this.


