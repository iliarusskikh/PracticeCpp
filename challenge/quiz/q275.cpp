#include <iostream>

int main()
{
    std::cout << (sizeof(long) > sizeof(int));
}
//unspecified behaviour
//The sizes of the standard integer types are not fixed by the standard. It's perfectly legal to, for instance, have an implementation where both long and int are 32 bits
