#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>


static uint32_t s_AllocCount=0;

void* operator new(size_t size){
    
    s_AllocCount++;
    std::cout << "Allocating "<<size<<" bytes";
    return malloc(size);
}

void PrintName(const std::string& name){
    std::cout << name << "\n";
}

void PrintNameStrView(std::string_view name){
    std::cout << name << "\n";
}



int main()
{
    //how to make strings performance faster
    //allocation on heap slows down the program
    std::string name = "Hehehe"; //heap allocation 1
    PrintName(name); //another allocation, when func param creates allocation
    
    std::string_view firstpart(name.c_str(),3);//3 chars
    PrintNameStrView(firstpart);//pointer to chars instead of creating a substring ; no mem allocations
    //
    
    // to get rid of all allocations, dont use function which has string as a param
    //also dont use strings - use const char* instead
    const char* naame = "No allocation";
    
    std::cout <<"Allocations: "<<s_AllocCount <<"\n";
    
    
    //sso small string optimisation
    //small strings not heap allocated.. up to certain length (16 chars)?
    
    std::string test = "MyTest";//allocated in stack in release mode .. for debug it would allocate on heap
    
    
    return 0;
}
