#include <iostream>
#include <fmt/core.h>

int main()
{
    fmt::print("Hello, \x1b[35m{}\x1b[0m!\n", "World"); //Hello, World
    //supports different styles and formats, more efficient than cout and printf
    return 0;
}
