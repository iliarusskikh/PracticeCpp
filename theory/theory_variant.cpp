// C++ program to show the different operator functions on std variant
#include <iostream>
#include <variant>

//store data of multiple datatype
//if you not sure at the moment what type of data will it be


int main()
{
    //c++ 17
    std::variant<std::string, int>data;//it stores all these datatypes as members
    data = "Cherno";
    //std::get<std::string>(data);
    std::cout << "Hello " << std::get<std::string>(data) << "\n";
    
    data.index(); //gives 0 for string and 1 for int - to understand what is the type at the moment
    data= 2;
    std::cout << "Hello " << std::get<int>(data) << "\n";

    
    if (auto* value = std::get_if<std::string>(&data)){
        //means wrong type
    }else{
        std::string& v= *value;// ← no copy, just another name
        //With & you get aliasing / no copy
    }
    
    return 0;
}

