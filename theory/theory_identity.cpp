//std::identity is a function object introduced in C++20. It returns its input unchanged and is primarily used in custom sorting, transformations, and projections with STL algorithms.
//std::ranges::sort(num, std::less<>(), [](int x) { return x; });

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

int main()
{
    std::vector<int> num = {3,1,4,1,5,9};
    std::ranges::sort(num, std::less<>(), std::identity{});
    for (int n: num)
        std::cout<<n <<" ";
    return 0;
}
