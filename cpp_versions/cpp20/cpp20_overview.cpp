//c++20
#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <coroutine>
#include <format>
#include <span>



generator<int> fibonacci(int n){
    int a=0, b=1;
    for(int i=0; i<n;++i){
        co_yield a; //suspends execution and resume later
        int tmp = a;
        a = b;
        b = tmp+b;
    }
}



//math.cppm moodule interface file
/*export module math;

export namespace math{
    int add(int a, int b){
        return a+b;
    }
}*/

//main.cpp using the module
import math;


//defining a concept
template<typename T>
concept Addable = requires(T a, T b){
    {a + b} -> std::convertible_to<T>;
};//adds constrains to templates

//using a concept
template<Addable T>
T add(T a, T b){
    return a+b;
}


//std::span non owning view over a contiguous sequence of objects
void process(std::span<int> data){
    for (auto item: data){
        //process each item
    }
}



int main()
{
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};
    //filter even numbers and transform them
    auto result = numbers
    | std::ranges::views::filter([](int n){ return n%2 ==0;})
    | std::ranges::views::transform([](int n){ return n*n;});
    
    std::string name "fefefef";
    //return math::add(2,3);
    
    
    std::string message = std::format("Welcome to {0}.", name);//inspired by python
    
    
    process(numbers);
    
    return EXIT_SUCCESS;
}
