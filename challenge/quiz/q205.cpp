#include <iostream>

int main() {
  constexpr unsigned int id = 100;
  unsigned char array[] = { id % 3, id % 5 };
  std::cout << static_cast<unsigned int>(array[0])
            << static_cast<unsigned int>(array[1]) ;
}
// Output: 10
//array is an array of unsigned char, but is initialized with unsigned ints. The unsigned ints have to be converted to unsigned chars, and since narrowing is not allowed in aggregate-initialization from an initializer list, we might expect a compilation error.
//So since id is constexpr, and both id % 3 and id % 5 fit in an unsigned char, the program is well-formed.
