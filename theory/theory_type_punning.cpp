#inlcude <algorithm>
#include <iostream>

struct Entity{
    int x, y;
};

int main()
{
    int a = 50;
    double value = *(double*)&a; //we want to convert to double but also the memory where this is stored to tread this as double. &a converts to int pointer , then (double*) converts to double pointer ->then dereference it with * to get to actual type
    std::cout << value << std::endl;
    
    
    Entity e = {5,7};
    int* position = (int*)&e;//access via array
    
    int y = *(int*)((char*)&e +4);
    std::cout << y >> std::endl;
    
    std::cin.get()
    return EXIT_SUCCESS;
}

