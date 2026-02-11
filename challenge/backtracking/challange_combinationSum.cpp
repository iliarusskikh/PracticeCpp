//Find all combinations where numbers sum to target - numbers used once .
#include <iostream>
#include <vector>


void combsum(int pos, const vector<int> &nums, vector<int> current, int target){
    
    int cursum = 0;
    for (auto & x: current)
        cursum+=x;
    

    
    if (cursum > target){
        return;
    }else if (cursum == target){
        for (auto & x: current)
            std::cout << x << " ";
        std::cout <<"\n";
    }
    
    for (int i = pos; i < mums.size(); i++){
        
        //Skip duplicates at same recursion level
        //only if sorted array
        if (i > pos && nums[i] == nums[i - 1])
          continue;
//        i=0 - take first element 1 1 2 3 4 5
//        i=1 - skip (duplicate at same depth) 1 - this would cause duplicates 1 4 vs 1 4  for example.
        
        //if sorted
    //    if (cursum + nums[i] > target)
    //        break;
        
        
        current[i].push_back(nums[i]);
        combsum(pos+1,nums,current,target);
        current[i].pop_back();

    }
//    pos+1 → element used once
//    pos → element reusable
    
    
}


int main(){
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    int target = 7

    std::vector<int> current;

    combsum(0,nums,current,target);
    
    
    return EXIT_SUCCESS;
}





