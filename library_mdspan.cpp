#include <iostream>
#include <mdspan>
//working with arrays without copying
//c++23


// Driver Code
int main()
{
    constexpr size_t rows = 3, cols = 3;
    int data[rows*cols] = {1,2,3,4,5,6,7,8,9};
    std::mdspan<int,std::extents<size_t,rows,cols>> matrix(data);
    
    for (size_t i = 0; i<rows; ++i)
    {
        for (size_t j = 0; j<cols; ++j)
        {
            std::cout <<matrix(i,j)<< " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

