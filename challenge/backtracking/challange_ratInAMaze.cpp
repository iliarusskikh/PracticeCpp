//O(4^(N*N))


//You are given a maze of size N × N represented as a matrix.
//1 = open path
//0 = blocked path
//A rat starts at the top-left corner (0,0) and wants to reach the bottom-right corner (N-1,N-1).
//The rat can move in four directions:
//Down (D)
//Left (L)
//Right (R)
//Up (U)
//
//Your task is to:
//Print all possible paths from start to destination.
//Print paths as strings like: "DRRD"

//Example:
//N = 4
//1 0 0 0
//1 1 0 1
//1 1 0 0
//0 1 1 1
//Output:
//DDRDRR
//DRDDRR

//Backtracking Idea
//From each cell:
//Try all 4 directions
//If safe → move
//Mark visited
//Recurse
//Backtrack (unmark visited)


#include <iostream>
#include <vector>

const int N = 4;

bool isSafe(int x, int y, std::vector<std::vector<int>>& maze, std::vector<std::vector<bool>>& visited){
    return (x >= 0 && y >= 0 &&
            x < N && y < N &&
            maze[x][y] == 1 &&
            visited[x][y] == false);
}

void solve(vector<vector<int>>& maze, int x, int y, std::vector<std::vector<bool>>& visited, std::string path)
{
    // Destination reached
    if (x == N - 1 && y == N - 1)
    {
        std::cout << path << "\n";
        return;
    }

    // Mark visited
    visited[x][y] = true;

    // Down
    if (isSafe(x + 1, y, maze, visited))
        solve(maze, x + 1, y, visited, path + 'D');

    // Left
    if (isSafe(x, y - 1, maze, visited))
        solve(maze, x, y - 1, visited, path + 'L');

    // Right
    if (isSafe(x, y + 1, maze, visited))
        solve(maze, x, y + 1, visited, path + 'R');

    // Up
    if (isSafe(x - 1, y, maze, visited))
        solve(maze, x - 1, y, visited, path + 'U');

    // Backtrack
    visited[x][y] = false;
}

int main()
{
    std::vector<std::vector<int>> maze =
    {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };

    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));

    solve(maze, 0, 0, visited, "");

    return EXIT_SUCCESS;
}
