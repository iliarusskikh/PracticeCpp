#include <iostream>
#include <typeinfo>

int main(){
    decltype(3+4.5) var;
    std::cout << typeid(var).name();
    return 0; //compiler determine var type only, not evaluating the value
}
