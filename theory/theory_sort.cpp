#inlcude <algorithm>
#include <iostream>



int main()
{

    std::vector<int> values = {1,2,34,6,88,53,1,3,5,7};
    
    std::sort(values.begin(), values.end(),[](int val1, int val2){
        if (val1 == 1)
            return false;
        if (val2 == 1)
            return true;
        return val1 < val2;});
    
    for (int value:values)
        std::cout << value << std::endl;
    
    return EXIT_SUCCESS;}

