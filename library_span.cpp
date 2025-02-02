#include <iostream>
#include <span>
#include <vector>

void printElements(std::span<int>data)
{
    for(int num : data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {10, 20 ,30 ,40 ,50};
    printElements(arr); //pass array, does not create extra copy
    printElements(vec); //pass vector without copying
    
    return 0;
}
