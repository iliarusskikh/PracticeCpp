//generate all subsets

#include <iostream>
#include <vector>

void subsets(int pos, const std::vector<int>& nums, std::vector<int>& current)){
    // Base case: processed all elements
    if (pos == nums.size()) {
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
        return;
    }
    
    //if less than total length
    // Choice 1: Include nums[index]
    current.push_back(nums[pos]);        // DO
    subsets(pos + 1, nums, current);
    current.pop_back();                    // UNDO

    // Choice 2: Exclude nums[index]
    subsets(pos + 1, nums, current);
    
    
}


//O(n/k)
void subsetswindow(int pos, const std::vector<int>& nums, std::vector<int>& current, int window)){
    if ((nums.size() - start) < (window - current.size())
        return;
    
// If we reached size k - solution found
    if (current.size() == window) {
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
        return;
    }

    //each element used once
    for (int i = pos; i < nums.size(); i++) {

        current.push_back(nums[i]);                 // DO

        subsetswindow(i + 1, nums, current, window);

        current.pop_back();                         // UNDO
    }
}



int main(){
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> current;

    subsets(0,nums, current);
//Total = 2^n subsets.
    
    int k = 3;
    subsetswindow(0,nums,current,k);
    
    
    return EXIT_SUCCESS;
}





