#include <functional>
#include <iostream>

template <typename T>
void call_with(std::function<void(T)> f, T val)
{
    f(val);
}

int main()
{
    auto print = [] (int x) { std::cout << x; };
    call_with(print, 42);
}
// Output: Compile error
//The compiler tries to deduce T for every parameter and checks if the deduced types match. Because a lambda is of completely different type, it cannot be matched against std::function<void(T)> and the deduction process fails.
