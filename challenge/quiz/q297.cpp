#include <future>
#include <iostream>

int main()
{
    auto f = std::async(std::launch::async, [](){ throw 0; });
    try {
        f.wait();
    } catch (...)
    {
        std::cout << 1;
    }
    std::cout << 2;
}
// Output: 2
//wait does not throw exceptions stored in the shared state.
//To get at the exception, you have to use get.
//So there's no exception thrown, the catch block is never entered, and the program only prints 2.


