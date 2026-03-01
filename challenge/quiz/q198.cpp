#include <iostream>

namespace A {
  extern "C" { int x; } //definition
};

//extern "C" int i;                   // declaration
namespace B {
  extern "C" { int x; }//definition
};

int A::x = 0;

int main() {
  std::cout << B::x;
  A::x=1;
  std::cout << B::x;
}

//Compiler error
//A::x and B::x actually refer to the same variable, and int x; is a definition, not a declaration. Defining the same variable twice results in a compilation error.

// All names declared inside the same extern "C" block (even in different namespaces) refer to the same global entity in the linkage namespace.
//→ both refer to the exact same global variable at link level
