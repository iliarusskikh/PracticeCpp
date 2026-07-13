//# Two sequences DP pattern: Compare two strings
//# Longest Common Subsequence Problem

//substring - no gaps
//subsequence - may be gaps between letters

int longestCommonSubsequence(std::string text1, std::string text2) {
    int m = text1.size();
    int n = text2.size();
    
   //m =0, n = 0, hence vector size + 1.
    // Create two rows: one for the previous iteration and one for the current
    std::vector<int> prev(n + 1, 0);
    std::vector<int> curr(n + 1, 0);
    
    // Iteratively build the DP table row by row
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                // If characters match, take the diagonal value + 1
                curr[j] = 1 + prev[j - 1];
            } else {
                // If they don't match, take the max from top (prev[j]) or left (curr[j-1])
                curr[j] = std::max(prev[j], curr[j - 1]);
            }
        }
        // Move the current row data to the previous row for the next iteration
        prev = curr;
    }
    
    // The last element contains the length of the longest common subsequence
    return prev[n];
}

int main(){

   std::string word1 = "helloween";
   std::string word2 = "hellonows";

   std::cout << lcs(word1,word2) <<std::endl;
   return 0;
}

//  0 T O W E R
//0 0 0 0 0 0 0 (empty substring)
//S 0 0 0 0 0 0
//T 0 1 1 1 1 1
//O 0 1 2 2 2 2
//N 0 1 2 2 2 2
//E 0 1 2 2 3 3
//
//
