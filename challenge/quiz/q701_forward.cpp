#include <iostream>
#include <utility>

void process (const std::string&){
    std::cout << "lvalue\n";
}

void process (const std::string&&){
    std::cout << "rvalue\n";
}


template<typename T>
void wrapper(T&& value){
    process(std::forward<T>(value))
}

int main(){
    std::string s = "Hello";
    wrapper(s);
    wrapper(std::string("world"));
}

//Output: lvalue rvalue
