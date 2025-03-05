//filesystem
#include <iostream>
#include <filesystem>


int main()
{
    std::filesystem::path file = "example.txt";
    
    if(std::filesystem::exists(file))
    {
        std::uintmax_t link_count = std::filesystem::hard_link_count(file);
        std::cout << "File "<< file << "Hard links " << link_count << std::endl;
        
        
    }
    return 0;
}
