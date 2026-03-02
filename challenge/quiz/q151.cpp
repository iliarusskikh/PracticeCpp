#include <iostream>
#include <type_traits>

int main()
{
    std::cout << std::is_signed<char>::value;
}
//Type char is a distinct type that has an implementation-defined choice of “signed char” or “unsigned char” as its underlying type.


