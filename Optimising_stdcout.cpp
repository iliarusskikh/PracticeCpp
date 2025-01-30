#include <iostream>
#include <chrono>

int main()
{
    const int iterations = 100000;
    
    //slow output
    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<iterations; ++i)
    {
        std::cout << "Hello " <<std::endl;
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1).count() << std::endl;
    
    
    //faster output with \n
    auto start2 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<iterations; ++i)
    {
        std::cout << "Hello \n";
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2).count() << std::endl;
}
