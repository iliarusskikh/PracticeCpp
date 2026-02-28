#include <iostream>

class A {
public:
  A() { std::cout << "a"; }
  ~A() { std::cout << "A"; }
};

int i = 1;

int main() {
label:
  A a;
  if (i--)
    goto label;
}

//The destructor runs before each goto jump because a goes out of scope when leaving its block, and also at the end of main().
//On exit from a scope (however accomplished), objects with automatic storage duration that have been constructed in that scope are destroyed in the reverse order of their construction.


