#include <iostream>
#include <scope>

void example()
{
    std::cout <<"open rss .. " << std::endl;
    std::scope_guard cleanup([]{ std::cout <<"closing rss .. " << std::endl;}); //this code is executed when exiting the function
    std::cout << "Do the excercise .." << std::endl;
}

int main()
{
    example();
    return 0;
}

