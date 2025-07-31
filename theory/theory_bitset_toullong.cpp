//bitset number converted to unsigned long long

#include <iostream>
#include <bitset>

int main()
{
    std::bitset<8>var("10010101");
    unsigned long long mynum =var.to_ullong();
    std::cout << mynum << std::endl;
    
    return 0;
}
