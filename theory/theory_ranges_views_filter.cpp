//C++20, filter elements without copying.
#include <iostream>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> vec = {1,2,3,4,5,5,6,7,8,9,10};
    
    auto even_num = vec | std::views::filter([](int n){return n % 2 == 0;});
    
    for (int n : even_num)
        std::cout << n << " ";
    return 0;
}

