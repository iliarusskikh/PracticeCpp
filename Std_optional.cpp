#include <iostream>
#include <string>
#include <optional>
//instead of using nullptr or -1, it will show if data is present

std::optional<std::string> findUser(int id)
{
    if (id == 1){
        return "Alice";
    }else{
        return std::nullopt;
    }
}


int main()
{
    auto user = findUser(2);
    if(user.has_value()){
        std::cout <<"User found" << user.value() << std::endl;
    }else{
        std::cout << "User not found" << std::endl;
    }
    
    std::cout<<"User: " <<user.value_or("Unknown") <<std::endl;
    
    return 0;
}
