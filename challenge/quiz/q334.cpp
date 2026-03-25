#include <iostream>

int f()
{
    std::cout << 1;
}

int main()
{
    f();
    std::cout << 2;
}

// Output: This is not a compilation error, but undefined behaviour.
//Flowing off the end of a constructor, a destructor, or a non-coroutine function with a cv void return type is equivalent to a return with no operand. Otherwise, flowing off the end of a function that is neither main nor a coroutine results in undefined behavior.
