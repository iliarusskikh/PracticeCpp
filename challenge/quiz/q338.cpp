#include <type_traits>
#include <iostream>
#include <string>

template<typename T>
int f()
{
    if constexpr (std::is_same_v<T, int>) { return 0; }
    else { return std::string{}; }
}

int main()
{
    std::cout << f<int>();
}

//Output: undefined
//In any hypothetical instantiation of f, std::string{} does not depend on the template parameter, and the instantiation would be ill-formed. So the program is ill-formed

//At the time of writing, GCC and Clang give a compilation error complaining they can't convert std::string to int, whereas MSVC prints 0.


