#include <iostream>
#include <print>

int main(){
    std::cout <<"Hello" << "\n";

    std::println("Hello");//23
    std::string stringg = std::format("Speed is {}", 5.4f);//cpp20
    std::println("Speed is {}", 5.4f); //contains format
    std::println()//cpp26 new line
    return EXIT_SUCCESS;
}
