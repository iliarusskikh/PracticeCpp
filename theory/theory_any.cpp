// C++17 program to show the different operator functions on ANY

//any type safety at run time, any type, dynamic allocation, memory usage higher

//std::variant - compile time, limited types, stack allocation, lower memory usage

//can store exactly one variable

#include <iostream>
#include <any>
//c++17

using namespace std;

void* operator new(size_t size){
    return malloc(size);
}


class Person{
public:
    Person(std::string n, int a): name(n), age(a){}

    std::string name;
    int age;
}



int main()
{
//std any - safe alternative to void pointers. type-safe container for single values of any copy constructible type
    
    std::any data;
    data = 2;
    data = "Gel"; //const char pointer
    //for small types stores as union, for large data - allocates memory dynamically
    //variant will be faster due to allocation
    data = std::string("Hello");
    std::string& kek = std::any_cast<std::string&>(data); //due to & we not getting memory allocation
    
    
    std::cout << " " <<"\n";
    
    
    std::any a = 91;
    
    if(a.has_value()){
        //
    }
    
    a.reset();//make empty
    //.type() - returns typeid of the contained value
    //.emplace<T>() - constructs the contained value in place
     
    std::any value = 91;
    //safe access with any_cast
    try{
        int i = std::any_cast<int>(value);
        std::cout << i << " ";//91
        
        double d = std::any_cast<double>(value);//would throw std::bad_any_cast;
        
    } catch (const std::bad_any_cast& e){
        std::cout << e.what() << " ";
    }
    
    if(value.type() == typeid(std::string)){
        //then ...
        //any_cast<std::string......
        //first check type then safe cast
    }
    
    std::cout <<value.type().name() <<" ";
    
    
    
    std::any da = Person("alice",33);
    if(data.type() == typeid(Person)){
        Person p = std::any_cast<Person>(da);
        std::cout << p.name << p.age;
    }
    
    
    
    
    return EXIT_SUCCESS;
}

