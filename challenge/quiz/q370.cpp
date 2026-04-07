#include <iostream>

enum A : const int volatile { x, y, z };

int main() {
  A a = A::x;
  a = A::y;
  std::cout << "ok";
}

//The type-specifier-seq of an enum-base shall name an integral type; any cv-qualification is ignored.
//
//So it's fine to add const and volatile here, they are ignored. The underlying type of A is simply int.
