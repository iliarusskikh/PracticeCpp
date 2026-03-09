#include <iostream>
#include <tuple>

int main()
{
    const auto t = std::make_tuple(42, 3.14, 1337);
    std::cout << std::get<int>(t);
    //    std::cout << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << "\n";

}

// Output:
//Compile error
//std::get<T>(tuple) can only be used on a tuple which has exactly one T in it.
