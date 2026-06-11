#include <iostream>
#include <typeinfo>

struct Base
{
};

struct Derived : Base
{
};

int main()
{
    Derived d;
    Base& b = d;
    std::cout << (typeid(b) == typeid(Derived));
}
// Output: 0
//b is a Base reference referring to an object of type Derived. But since Base has no virtual functions, there is no runtime type information for it, and typeid(b) returns the type Base rather than Derived. The comparison returns false, and 0 is printed.



