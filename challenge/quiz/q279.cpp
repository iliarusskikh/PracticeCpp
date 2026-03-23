#include <iostream>
#include <variant>

struct C
{
    C() : i(1){}
    int i;
};

struct D
{
    D() : i(2){}
    int i;
};

int main()
{
    const std::variant<C,D> v;
    std::visit([](const auto& val){ std::cout << val.i; }, v);
}
// Output: 1
//std::variants default constructor constructs a variant holding the value-initialized value of the first alternative. So it picks C as the type and calls the C::C() default constructor initializing it with i == 1, which gets printed.

