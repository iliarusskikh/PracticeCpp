#include <iostream>
#include <vector>

struct Foo
{
    Foo() { std::cout<<"a"; }
    Foo(const Foo&) { std::cout<<"b"; }
};

int main()
{
    std::vector<Foo> bar(5);
}
// Output: aaaaa
//C++11 vector init
