#include <iostream>
#include <functional>

void greet(const std::string& prefix, const std::string& name){
    std::cout << prefix <<" , "<<name << "!"<<std::endl;
}

int main()
{
    auto say_hello = std::bind_front(greet,"Hello");
    say_hello("Josh");
    say_hello("Bob");
    
    return 0;
}

