//
//# House Robber

#include <vector>
#include <algorithm>

int houseRobber(const std::vector<int>& nums) {
    int n = nums.size();
    
    // Edge cases: handle small street sizes to prevent out-of-bounds errors
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int first = nums[0];
    int second = std::max(nums[0], nums[1]);

    // Iteratively step through the houses from index 2 up to n-1
    for (int i = 2; i < n; ++i) {
        // You can either rob the current house + what you had 2 houses ago,
        // or skip the current house and keep what you had 1 house ago.
        int current = std::max(first + nums[i], second);
        first = second;
        second = current;
    }
    
    // 'second' always holds the maximum possible loot at the end of the street
    return second;
}

