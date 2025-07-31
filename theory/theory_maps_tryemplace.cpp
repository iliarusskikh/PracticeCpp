//try emplace = method which add element if its key currently missing (no other keys presented)

#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::unordered_map<std::string, std::string> data;
    data.try_emplace("user", "BoB");
    data.try_emplace("user", "Helen"); //key USER already presented, hence, not added
    
    return 0;
}

