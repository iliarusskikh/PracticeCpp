#include <iostream>

int main() {
  int n = 1;

  std::cout << (*reinterpret_cast<char *>(&n) == 1) << std::endl;
  return 0;
}
/*
 
 However, what value is read depends on how the implementation chooses to represent an int in memory.
 The standard says that the object representation of a trivially copyable type is
 implementation-defined. In practice, this usually corresponds to the machine’s endianness.

 For instance, on a little-endian machine with 32-bit ints, the int value 1 might be stored as:

 0x01 0x00 0x00 0x00
 while on a big-endian machine, it might be:

 0x00 0x00 0x00 0x01
 When cast to a char* and dereferenced, assuming 8 bit chars, the little-endian machine will read the first byte as 0x01,
 while the big-endian machine will read 0x00.

 Therefore, the program's behavior is well-defined, but the output is implementation-defined. It will print 1 on a little-endian machine, and 0 on a big-endian machine.
 */
