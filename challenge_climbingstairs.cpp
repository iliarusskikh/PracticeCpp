// climbing stairs 

// C++ program to count number of ways 
// to reach nth stair using Tabulation

#include <iostream>
#include <vector>
using namespace std;

int countWays(int n) {
    vector<int> dp(n + 1, 0);
  
    // Base cases
    dp[0] = 1;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2]; 
  
    return dp[n];
}

int main() {
    int n = 4;
    cout << countWays(n);
    return 0;
}
