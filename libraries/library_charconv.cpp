#include <iostream>
#include <charconv>

int main()
{
    std::string str= "1244";
    int value = 0;
    
    auto result = std::from_chars(str.data(), str.data() + str.size(), value);
    if (result.ec == std::errc()){
        std::cout <<"Number  "<< value << std::endl;
    }else
    {
        std::cout <<"error  " << std::endl;
    }
    
    
    return 0;
}

