//c++20, printf with secure types and readible syntax
#include <iostream>
#include <format>

int main()
{
    int age =25;
    double pi = 3.14159;
    std::string name = "Alice";
    std::string formatted = std::format("Name: {}, age {} , pi {:.2f}",name,age,pi);
    std::cout << formatted<<std::endl;
    
    return 0;
}
