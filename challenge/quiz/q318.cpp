#include <iostream>

struct S {
  operator void() {
    std::cout << "F";
  }
};

int main() {
  S s;
  (void)s;
  static_cast<void>(s);
  s.operator void();
}
// Output: F
//In this program, the object s is converted to void in three ways. First with a C-style cast, then with a static_cast, and finally by manually calling the conversion function.

//According to the C++ standard, conversion functions will never be used to convert an object to void. So the conversion function is only called once, when we manually call it on the line s.operator void();.
