//determines wether big or little Indian of the system
#include <iostream>
#include <bit>

int main()
{
    if constexpr(std::endian::native == std::endian::little)
        std::cout <<"system little endian" << std::endl;
    else if constexpr(std::endian::native == std::endian::big)
        std::cout <<"system big endian" << std::endl;
    else
        std::cout <<"unknown " << std::endl;

    return 0;
}

