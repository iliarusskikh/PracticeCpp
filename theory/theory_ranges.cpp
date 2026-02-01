//C++20, filter elements without copying.

#include <iostream>
#include <vector>
#include <ranges>

int main(){
    using namespace std::views;
    
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    auto d = v |
    filter([](int x){return x % 2 == 1;}) | //Keep only odd numbers (x % 2 == 1)
    transform([](int x){return x * 2;}) | //Multiply each remaining element by 2
    take(5) | //Take at most first 5 elements (here only 2 exist → no change)
    drop(1) | //Skip/drop the first 1 element
    reverse; //Reverse the order of the remaining elements
    
    
    
    auto slice = v | drop(1) | take(2);
    
    
    
    std::vector<int> vec = {1,2,3,4,5,5,6,7,8,9,10};
    
    auto even_num = vec | std::views::filter([](int n){return n % 2 == 0;});
    
    for (int n : even_num)
        std::cout << n << " ";
    
    
    return EXIT_SUCCESS;
    
}
