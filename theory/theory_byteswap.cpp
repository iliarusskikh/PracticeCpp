//big endian to little endian vv
#include <iostream>
#include <bit>


int main()
{
    uint32_t value= 0x12345678;
    uint32_t swapped = std::byteswap(value);//order of bytes
    
    std::cout << "0x"<<swapped<<std::endl; //0x78563412
    return 0;
}

