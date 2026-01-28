#include <iostream>
#include <print>
#include <expected>

std::expected<int, std::string> Divide(int a, int b){
    if (b==0)
        return std::unexpected("Divide by 0 error!");
    
    return a/b;
}

int main(){
    
    auto result = Device(10,2);
    if (result){
        std::println("Result = {}", *result);
        
    }else{
        std::println("Error: {}", result.error());
    }
    std::cout <<"Hello" << "\n";

    return EXIT_SUCCESS;
}
