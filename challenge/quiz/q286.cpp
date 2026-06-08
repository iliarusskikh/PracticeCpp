#include <iostream>

int main()
{
    unsigned short x=0xFFFF;
    unsigned short y=0xFFFF;
    auto z=x*y;
    std::cout << (z > 0);
}
// Output: undefined behaviour
//In summary: x and y are both converted to another type before being multiplied. On most systems (64-bit Windows/Linux/macOS for instance), that type is int, which is commonly 32 bits signed. 0xFFFF * 0xFFFF can't fit in a signed 32 bit type, and we get signed integer overflow, which is undefined behavior.

