#include <iostream>
#include <bit>


int main()
{
    unsigned int x= 40; //101000
    std::cout << std::countr_zero(x)<<std::endl;//000, 3
    return 0;
}

