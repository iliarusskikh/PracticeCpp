#include <iostream>
#include <stdexcept>

int main()
{
    goto inside;
    try
    {
        inside:
        throw std::runtime_error("oops");
    }
    catch(...)
    {
        std::cout << 1;
    }
    std::cout << 2;
}
//compiler error
//You may not use goto to enter the body of a try block.
//You may not use goto to jump from outside a try block directly to a label inside its compound statement.
