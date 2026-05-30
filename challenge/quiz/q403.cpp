#include <cstdlib>
#include <iostream>

int main()
{
    const auto output = "abs of -8" + std::abs(-8);
    std::cout << output;
}
// Output: 8

