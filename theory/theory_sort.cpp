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
    
    
    
    std::vector<int> vv = {3,1,5,7,1,3,5,7,8,2};
    
    //std::sort - general purpose sorting algo, quicksort/heapsort/insertion sort
    std::sort(vv.begin(), vv.end());
    std::sort(vv.begin(), vv.end(), [](int a, int b){return a>b;});//descending order
    

    //std::stable sort - maintains relative order of equal elements
    std::stable_sort(vv.begin(),vv.end());
    //std::partial_sort - sort a specified number of elements
    
    //std::nth_element - partially sorts to find the nth element
    
    //bubble sort | selection sort | insertion sort | merge sort | quick sort | heap sort
    
    
    
    
    
    
    
    return EXIT_SUCCESS;
    
}

