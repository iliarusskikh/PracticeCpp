#include <iostream>

int main() {
  unsigned i = 0;
  for (; i < 2; ++i) {
    std::cout << i << " ";
  }
  for (; i >= 0; --i) {//unsigned overflow causes infinite loop
    std::cout << i << " ";
  }
}

// Output: unspecified implementation:

//First, i is initialized to 0.

//Then, in the first loop, we print and increment i as long as it's < 2. So this loop prints 0 and 1 before it reaches 2 and we break out of the loop.
//
//Then, in the second loop, i starts out as 2, then we print and decrement it as long as it's >=0. But since i is unsigned, it never becomes negative. Some compilers will warn you about this, but not all! This loop prints 2, 1, and 0. Then i wraps around to the largest unsigned value, such as 4294967295 (depending on your platform), and keeps decrementing, printing, and wrapping around, in an infinite loop.
