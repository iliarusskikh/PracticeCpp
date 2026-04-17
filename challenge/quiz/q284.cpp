#include <iostream>
#include <string>

auto main() -> int {
  std::string out{"Hello world"};
  std::cout << (out[out.size()] == '\0');
}
// Output: 1
//operator[](size_type pos) must return a reference to the null character when pos equals the length of the string:
// So out[out.size()] == '\0' compares a character with value 0 to a character literal '\0'.
//\0 is an octal escape sequence, so the value of '\0' is indeed 0. The comparison is true, and 1 is printed.
