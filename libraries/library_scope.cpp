//c++23 score_exit allows automatically execute code when outside visible zone. useful when releasing resources and cancelling operations without try/catch
#include <iostream>
#include <scope>

void example()
{
    std::cout <<"open rss .. " << std::endl;
    std::scope_exit cleanup([]{ std::cout <<"closing rss .. " << std::endl;}); //this code is executed when exiting the function
    std::cout << "Do the excercise .." << std::endl;
    
    
}

int main()
{
    
    example();
    return 0;
}
