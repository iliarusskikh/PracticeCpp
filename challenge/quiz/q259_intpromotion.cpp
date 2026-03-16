
#include <iostream>

void f(unsigned int) { std::cout << "u"; }
void f(int)          { std::cout << "i"; }
void f(char)         { std::cout << "c"; }

int main() {
    char x = 1;
    char y = 2;
    f(x + y);
    
    return 0;
}
//undefined

//The type of the sum of two chars is actually not uniquely specified. We do however know it's not char.
//
//Before being passed to operator +, the operands (x and y) go through a conversion.
//So in practice, most systems will call f(int) and print i, but some might call f(unsigned int) and print u, and they would both be conforming to the standard.


