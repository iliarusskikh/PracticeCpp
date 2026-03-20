#include <iostream>

int main()
{
    int i = 1;
    int& j;
    j = i;
    std::cout << j;
}
// Compiler error
//References must be immediately initialized. Not initializing j is a compilation error.
