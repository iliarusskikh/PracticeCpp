#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
void check_type(T value){
    if (std::is_integral<T>::value){
        std::cout <<"Is integral type";
    }else if (std::is_floating_point<T>::value){
        std::cout << "Is floating point";
    }
    
    
    //c++17 variable templates
    if(std::is_integral_v<T>){
        //integer-specific code
    }
}

//type categoties
//std::is_array<T>::value
//std::is_pointer<T>::value
//std::is_reference<T>::value
//std::is_class<T>::value

//type properties
//is_const
//is_volatile
//is_signed
//is_unsigned
//is_abstract

//type transformations
//remove_const
//remove_reference
//add_pointer
//decay - applies type conversions like in function calls

//type relationships
//is_same
//is_base_of
//is_convertible
//is_constructible

//type operations
//conditional
//enable_if
//common_type
//underlying_type



//compile-time function selection based on type properties
tempalte<typename T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
process(T value){
    //Integer-specific implementation
    return true;
}

//this tempalte is only enabled for floating point types
//can be used for overloading
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
process(T value){
    //floating point implementation
    return false;
}



//type transformations
//remove reference and cv-qualifiers
template<typename T>
using clean_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

//perfect forwarding with decay
template<typename T>
void wrapper(typename std::decay<T>::type value){
    //implementation
}

//conditional type selection
template<typename T>
using number_type = typename std::conditional<std::is_floating_point<T>::value, double, int>::type;

//adding const to a type
template<typename T>
using const_type = typename std::add_const<T>::type;

//c++14
template<typename T>
using remove_ref_t = std::remove_reference_t<T>;



//concepts
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

//using a concept in a function template
template<Numeric T>
T add(T a, T b){
    return a+b;
}

//alternative
template<typename T>
    requires std::is_arithmetic_v<T>
T multiply(T a, T b){
    return a*b;
}




//optimised container based on type properties
template<typename T>
class OptimizedVector{
private:
    //use std::vector for non trivial types
    //use plain array for trivial types
    using StorageType = typename std::conditional<std::is_trivially_copyable_v<T>, T*, std::vector<T>>::type;
    
    StorageType storage;
    size_t size_;
  
public:
    //implementation
};



int main(){
    
    return EXIT_SUCCESS;
}
