
#include <iostream>

//move constructor
student (student&& other)
{
    name = other.name;
    age = other.age;
    other.name = NULL;
}
//vs
student(const student& copy) : age(copy.age), name(copy.name)
{
    
}


//move assignment
student& operator=(student&&other)
{
    if (this != &other)
    {
        if(name)
        {
            delete name;
        }
        age = other.age;
        name = other.name;
        other.name = NULL;
    }
    
    return *this;
}
//vs
student& operator=(const student& copy)
{
    age = copy.age;
    name = copy.name;
    
    return *this;
}

//destructor
~student()
{
    
}
