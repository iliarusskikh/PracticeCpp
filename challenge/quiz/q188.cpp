#include <iostream>

int main() {
  char* a = const_cast<char*>("Hello");
  a[4] = '\0';
  std::cout << a;
}
// Output:Undefined
//Modifying string literals is undefined behavior. In practice, the implementation can for instance store the string literal in read-only memory, such as the .rodata segment on Linux. Two string literals might even be stored in overlapping memory. So allowing them to be modified is clearly not a good idea.


