//Rotten Oranges - Minimum Time to Rot All

//Given a matrix of dimension mxn, where each cell in the matrix can have values 0, 1 or 2 which has the following meaning:
//
//0: Empty cell
//1: Cells have fresh oranges
//2: Cells have rotten oranges

//The task is to find the minimum time required so that all the oranges become rotten. A rotten orange at index (i,j) can rot other fresh oranges which are its neighbors (up, down, left, and right).
//
//Note : If it is impossible to rot every orange then simply return -1.



//[Naive Approach] - Using Iteration - O((n x m) ^ 2) Time and O(1) Space

//The idea is iteratively change the cells with fresh orange connected to that of rotten orange until either there is no cell with fresh orange or it is not possible to reach the fresh orange.
/*
#include <bits/stdc++.h>
using namespace std;

bool isSafe(int i, int j, int n, int m) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int orangesRotting(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    // to check if any changes are made
    bool changed;

    // counter of elapsed time
    int elapsedTime = 0;

    // all four directions
    vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    // iterate until changes are there
    while (true) {
        changed = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // check if the cell was marked in last iteration
                if (mat[i][j] == elapsedTime + 2) {
                    // change 4-directionally connected cells
                    for (const auto& dir : directions) {
                        int x = i + dir[0]; //x
                        int y = j + dir[1]; //y
                        // if cell is in the matrix and the orange is fresh
                        if (isSafe(x, y, n, m) && mat[x][y] == 1) {
                            mat[x][y] = mat[i][j] + 1;
                            changed = true;
                        }
                    }
                }
            }
        }
        // if no changes are done
        if (!changed) {
            break;
        }
        elapsedTime++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // if any orange is found not rotten, return -1
            if (mat[i][j] == 1) {
                return -1;
            }
        }
    }

    return elapsedTime;
}

int main() {
    vector<vector<int>> mat = {{2, 1, 0, 2, 1}, {1, 0, 1, 2, 1}, {1, 0, 0, 2, 1}};
    cout << orangesRotting(mat) << endl;
    return 0;
}

*/


//[Expected Approach] - Using Breadth First Search - O(n x m) Time and O(n x m) Space

#include <bits/stdc++.h>
using namespace std;

// Check if i, j is within the array
// limits of row and column
bool isSafe(int i, int j, int n, int m)
{
    return (i >= 0 && i < n && j >= 0 && j < m);
}

int orangesRotting(vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();

    vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};    // all four directions

    queue<vector<int>> q;    // queue to store cell position


    // find all rotten oranges
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 2)
            {
                q.push({i, j});
            }
        }
    }

    // counter of elapsed time
    int elapsedTime = 0;

    while (!q.empty())
    {

        // increase time by 1
        elapsedTime++;

        int len = q.size();
        while (len--)
        {
            vector<int> cur = q.front();
            q.pop();
            int i = cur[0];
            int j = cur[1];

            // change 4-directionally connected cells
            for (auto dir : directions)
            {
                int x = i + dir[0];
                int y = j + dir[1];

                // if cell is in the matrix and
                // the orange is fresh
                if (isSafe(x, y, n, m) && mat[x][y] == 1)
                {
                    mat[x][y] = 2;
                    q.push({x, y});
                }
            }
        }
    }

    
    // check if any fresh orange is remaining
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 1)
            {
                return -1;
            }
        }
    }

    return max(0, elapsedTime - 1);
}

int main()
{
    vector<vector<int>> mat = {{2, 1, 0, 2, 1}, {1, 0, 1, 2, 1}, {1, 0, 0, 2, 1}};
    cout << orangesRotting(mat);
    return 0;
}
