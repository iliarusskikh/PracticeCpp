// C++ program to show the different operator functions on ANY

#include <iostream>
#include <any>
//c++17

using namespace std;

void* operator new(size_t size){
    return malloc(size);
}

int main()
{
//std any
    
    std::any data;
    data = 2;
    data = "Gel"; //const char pointer
    //for small types stores as union, for large data - allocates memory dynamically
    //variant will be faster due to allocation
    data = std::string("Hello");
    std::string& kek = std::any_cast<std::string&>(data); //due to & we not getting memory allocation
    
    
    std::cout << " " <<"\n";
    
    return EXIT_SUCCESS;
}

