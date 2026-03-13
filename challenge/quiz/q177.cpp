#include <limits>
#include <iostream>

int main() {
    std::cout << std::numeric_limits<unsigned char>::digits;
}
//uncertain output
//Although this program probably outputs 8 on your computer, it's not guaranteed to do so by the standard. All we can be sure of is that it's at least 8 bits.

//So unsigned char is the same width as signed char, which is at least 8 bits.
