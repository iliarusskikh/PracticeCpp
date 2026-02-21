//C++23 hive container for high frequency additions and deletions withouth mem fragmentation
//unlike list and vector, more effective and iterative
#include <iostream>
#include <memory>
#include <vector>
#include <hive>

int main()
{
    std::hive<int> num;
    num.insert(10);
    num.insert(20);
    num.insert(14);
    
    for(int n: num)
    {
        std::cout << n << std::endl;
    }
    return 0;
}

