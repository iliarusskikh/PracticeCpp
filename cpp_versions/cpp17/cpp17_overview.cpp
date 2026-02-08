//c++17
#include <iostream>
#include <string>
#include <optional>




std::optional<std::string> findUserName(int id){
    if (id ==12){
        return "Bob Bou";
    }
    return std::nullopt; //no value
}

//if (name){*name}



//inline variables - not breaching ODR One Definition Rule in header files
namespace math{
inline constexpr double PI = 3.145427245136357243144;
inline constexpr double E = 1.23125136357243144;
}


//before
/*
 template<typename T, typename... Args>
 T sum(T first, Args.... args){
    return first + sum(args...);//recursive approach
 }
 */


template<typename... Args>
auto sum(Args... args){
    return (args + ...); //unary right fold
}




std::tuple<int,std::string,double> getData(){
    return {44,"Gee", 4.13};
}

template<typename T>
auto process(T value){
    if constexpr(std::is_integral_v<T>){
        //compile-time if, integrer implementation
        return value *2;
    }else if constexpr(std::is_floating_point_v<T>){
        //non-integer
        return value * 3.11;
    }else
    {
        return value;
    }
}




int main()
{
    //structured bindings before C++17
    int id;
    std::string name;
    double value;
    
    std::tie(id,name,value) = getData();
    
    auto [id,name, value] = getData(); // with C++17
    
    //variant
    //any
    
    
    return EXIT_SUCCESS;
}
