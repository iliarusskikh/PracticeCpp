#include <iostream>
#include <stdexcept>

void risky() { throw std::runtime_error("Error!"); }

int main()
{
    try { risky(); }
    catch (const std::exception& e) { std::cout << e.what() << std::endl; }
}
