//std::generator allows creating lazy generators whcih evaluate functions
//Efficient Lazy Evaluation → Generates values only when needed.
//No Preallocation Required → No need to store large arrays...
//Saves Memory → Only one number is held in memory at a time.
//Great for Infinite Sequences → You can generate endless numbers without memory issues.
#include <iostream>
#include <generator>

std::generator<int>fibonacci(int n)
{
    int a = 0, b = 1;
    for(int i = 0; i<n; ++i)
    {
        co_yield a; //returns then continues
        int temp = a;
        a = b;
        b = temp + b;
    }
}

int main()
{
    for(int num : fibonacci(10))//since everytime it hits co_yield, it returns int. here it triggers and num reads it out
    {
        std::cout << num << std::endl;
    }
    
    return 0;
}

