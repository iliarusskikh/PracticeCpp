// Number of ways
//# Climbing Stairs Problem

function climbStairs(n){
   if (n == 1) return 1;
   if (n == 2) return 2;
   return climbStairs(n-1) + climbStairs(n-2);
}

//# when using memoisation - top-down approach.
//
//# Climbing Stairs Problem with Tabulation Space/Time O(n) - bottom-up

int climbStairs(int n) {
    // Handle base cases immediately
    if (n <= 1) return 1;
    
    // Create a memo table initialized to 0
    std::vector<int> memo(n + 1, 0);
    
    // Define base states
    memo[0] = 1;
    memo[1] = 1;
    
    // Fill the table iteratively (Bottom-Up Memoization)
    for (int i = 2; i <= n; ++i) {
        memo[i] = memo[i - 1] + memo[i - 2];
    }
    
    return memo[n];
}




//# Minimum cost climbing stairs - bottom up Space/Time O(n)
// only using last two variables

#include <vector>
#include <algorithm>

int minCostClimbingStairsSpaceOptimized(std::vector<int>& cost) {
    int first = cost[0];
    int second = cost[1];
    
    // Iteratively step through the array from index 2 up to n
    for (size_t i = 2; i < cost.size(); ++i) {
        int current = cost[i] + std::min(first, second);
        first = second;
        second = current;
    }
    
    // The top floor is 1 step past the final array element
    return std::min(first, second);
}


