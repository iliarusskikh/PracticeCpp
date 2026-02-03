// Modifying algorithms

#include <iostream>
#include <vector>
#include <algorithms>



int main()
{
    //copy operations
    //copy , copy_if, copy_n, copy_backward
    std::vector<int> source = {1,2,3,4,5,6};
    std::vector<int> destination(6);
    
    //copy all elements from source to dest
    std::copy(source.begin(),source.end(), destination.begin());
    
    std::vector<int> even_numbers;
    //copy if satisfies the condition
    std::copy_if(source.begin(),source.end(),
                 std::back_inserter(even_numbers), [](int n){return n% 2 == 0;});
    
    //copy_n n elements from source
    //backward - reverse order
    std::copy_n(source.begin(),3, destination.begin());
    std::copy_backward(source.begin(),source.end(), destination.end());

    
    std::vector<int> nums = {1,2,3,4,5,6};
    std::vector<int> nums2 = {1,2,3,4,5,6};

    std::vector<int> results (6);
    //transform, replace, replace_if, repalce_copy
    //used either on single range or two ranges
    std::transform(nums.begin(), nums.end(), result.begin(), [](int n){return n*n;});
    //binary operations , combining two containers
    std::transform(nums.begin(), nums.end(), nums2.begin(), result.begin(), std::plus<int>());
    
    //replace - all values equal to old value with new value
    std::vector<int> v1 = {1,2,3,4,5,6};
    //replace all 2 with 5;
    std::replace(v1.begin(),v1.end(),2,5);
    
    //replace values > 4 with 100;
    std::replace_if(v1.begin(),v1.end(),[](int n){return n>4;}, 100);
    
    //replace and copy into dest, original vector unaffected
    std::replace_copy(v1.begin(),v1.end(), result.begin(),2,9);//replace all 2 with 9 in the copy
    std::replace_copy_if(v1.begin(),v1.end(), [](int n) {return n < 3;},0);//replace all values < 3 with 0 in the copy
    

    //std::fill assigns a value to all elements in a range
    //fill_n assigns a value to the first n elements in a range
    std::fill(v1.begin(),v1.end(), 42);//full entire vector with 42;
    std::array<int,4>arr;
    std::fill_n(arr.begin(),3,100);//fill first 3 elements with 100
    
    
    //generate, generate_n - fill with values from a generator function
    std::vector<int> vv1 = {1,2,3,4,5,6};
    std::vector<int> vv2(6);
    std::mt19937 rng(std::random_device{}());
    
    std::generate(v2.begin(), v2.end(), [&rng](){return rng() % 100;});//random
    //swap_ranges - exchange elements between ranges
    std::swap_ranges(v1.begin(),v1.begin() + 3, v2.begin());//swap first 3 elements
    //move move elements from source to destination
    
    //remove/remove_if - removes elements from a range
    
    //unique - remove consecutive duplicates
    //you can sort first
    std::vector<int> vvv = {1, 2, 2, 3, 3, 1, 4, 4};
    auto last = std::unique(vvv.begin(), vvv.end());//Removes consecutive duplicates by moving unique elements forward
    //it only rearranges the elements and returns an iterator pointing to the first "garbage" element.
    vvv.erase(last, v.end());//last is iterator from which element apply the deletion
    
    
    return EXIT_SUCCESS;
}


