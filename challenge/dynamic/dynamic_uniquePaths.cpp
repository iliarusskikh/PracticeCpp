//# Grid Pattern
//# Unique paths problem

paths[i,j] = paths[i-1,j] + paths[i, j-1]


#include <vector>

int uniquePaths(int m, int n) {
    // If the grid is empty, no paths exist
    if (m <= 0 || n <= 0) return 0;

    // Use a single row vector instead of a full m x n grid
    // Initialize with 1s because there is exactly 1 way to move along the first row
    std::vector<int> row(n, 1);

    // Iteratively build out the paths row by row
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            // row[j] is paths[i-1][j] (above)
            // row[j-1] is paths[i][j-1] (left)
            row[j] += row[j - 1]; // in fact updating current row
        }
    }

    // The last element contains the unique paths to the bottom-right corner
    return row[n - 1];
}
//Time Complexity: O(m × n)
//Space Complexity: O(n)

