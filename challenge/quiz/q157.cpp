#include <iostream>
#include <typeinfo>

struct A {};

int main()
{
    std::cout<< (&typeid(A) == &typeid(A));
}
// Output: undefined
//There is no guarantee that the same std::type_info instance will be referred to by all evaluations of the typeid expression on the same type, although std::type_info::hash_code of those type_info objects would be identical, as would be their std::type_index.
