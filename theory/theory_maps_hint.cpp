#include <iostream>
#include <unordered_map>


int main()
{
    std::unordered_map<std::string, int> data;
    auto hint = data.end();
    hint = data.emplace_hint(hint, "Alice",25);//updates hint with new position
    data.emplace_hint(hint,"Bib",29);
    
    
    return 0;
}

