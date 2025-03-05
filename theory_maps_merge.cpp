//C++20, merging maps elements
#include <iostream>
#include <unordered_map>


int main()
{
    std::unordered_map<int, std::string> map1 = {{1,"alice"}, {2,"bob"}};
    std::unordered_map<int, std::string> map2 = {{3,"Hoho"}, {2,"duplicate"}};
    
    map1.merge(map2);//2,dup not copied
    for(const auto&[key,value] : map1)
    {
        std::cout << key << " " <<value << std::endl;
    }
    
    for(const auto x : map1)
    {
        std::cout << x.first << " " <<x.second << std::endl;
    }
    
    return 0;
}

