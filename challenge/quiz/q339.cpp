#include <future>
#include <iostream>

int main()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();
    p.set_value(1);
    std::cout << f.get();
    std::cout << f.get();
}
// Output: undefined
//You can only get the value from a future once. It is undefined behaviour to call get multiple times, but implementations are encouraged to throw an exception, and most (such as GCC, Clang and MSVC) also do so at the same of writing.
