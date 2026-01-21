// C++ program to show the different operator functions on structured bindings
#include <iostream>
#include <tuple>
#include <string>


//function that return multiple variables via tuple
std::tuple<std::string, int> CreatePerson(){ //or pair for two values
    return {"Bob", 24};
}


int main()
{

    //first way
    std::tuple<std::string,int> person = CreatePerson();
    std::string&  name = std::get<0>(person);
    int age = std::get<1>(person);
    
    //second way
    std::string name;
    int age;
    std::tie(name,age) = CreatePerson();
    
    //third way c++17
    auto[name,age] = CreatePerson();
    std::cout << "Hello " << name << "\n";
    
    
    
    return 0;
}

