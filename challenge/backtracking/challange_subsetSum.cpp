//Does there exist a subset whose sum equals target?
//This introduces early termination propagation.
//Worst case → O(2^n)

#include <iostream>
#include <vector>

bool subsetSum(int pos, const std::vector<int>& nums, int current_sum, int target)
{
    // Found solution
    if (current_sum == target)
        return true;

    // Exhausted elements
    if (pos == nums.size()) //no solution found yet
        return false;

    // Prune if sum exceeds target (assuming positive numbers)
    if (current_sum > target)
        return false;

    // Choice 1: Take element
    if (subsetSum(pos + 1, nums, current_sum + nums[pos], target))
        return true;   // propagate success immediately

    // Choice 2: Skip element
    if (subsetSum(pos + 1, nums, current_sum, target))
        return true;

    return false;
}



int main() {
    std::vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;

    std::cout << std::boolalpha << subsetSum(0, nums, 0, target) << "\n";

    return EXIT_SUCCESS;
}


