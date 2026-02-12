
//Place N queens on an N × N chessboard such that:
//No two queens share the same row
//No two queens share the same column
//No two queens share the same diagonal

//A queen attacks:
//Entire row
//Entire column
//Both diagonals

//Same row:    (row, any_col)
//Same column: (any_row, col)
//Main diagonal:     row - col is constant
//Anti diagonal:     row + col is constant

//We enforce:
//One queen per row.

//Now we only need to check:
//Column conflict
//Diagonal conflicts

//Main diagonal index = row - col + (N - 1)
//Anti diagonal index = row + col


/*
 Approach:
 One queen per row (recursion depth = row)
 Track constraints with:
 columns[col]
 diag1[row - col + (n - 1)]
 diag2[row + col]
 Build board as vector<string>
 Store solutions when row == n
 No globals. Everything passed by reference.
 */

#include <iostream>
#include <vector>
#include <string>

// . Q . .
// . . . Q
// Q . . .
// . . Q .

bool isSafe(int row, int col, std::vector<string>& board, int n)
{
    //Same row:    (row, any_col)
    //Same column: (any_row, col)
    //Main diagonal:     row - col is constant
    //Anti diagonal:     row + col is constant
    
    
    // Check column - no other Q in given column - iterate through rows
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q')
            return false;

    
    //we only need to check upper diagonals, since bottom ones not populated yet
    
    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--)
        if (board[i][j] == 'Q')
            return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n;
         i--, j++)
        if (board[i][j] == 'Q')
            return false;

    return true;
}


void solve(int row, std::vector<std::string>& board, int n){
    if (row == n) {
        for (auto& r : board) //Safe Q placed
            std::cout << r << "\n";
        std::cout << "--------\n";
        return;
    }

    for (int col = 0; col < n; col++) { //traverse through columns
        //if smth is not safe, we miss row increment, hence row != n. would not become a solution
        if (isSafe(row, col, board, n)) { //check current position to place Q

            board[row][col] = 'Q';   // DO

            solve(row + 1, board, n); //continue with next row. if it was safe and we continue with next, on the N iteration, it means that all Q placed and we can print the last one in base case.

            board[row][col] = '.';   // UNDO
        }
    }
}


//Version 1:
//Safety check = O(n)
//Total complexity ≈ O(n!)
//Version 2:
//Safety check = O(1)
//Much faster for large N




//Column index = col
//Main diagonal = row - col + (n - 1)
//Anti diagonal = row + col
void solve(int row, std::vector<string>& board, std::vector<bool>& columns, std::vector<bool>& diag1, std::vector<bool>& diag2, int n)
{
    if (row == n) {
        for (auto& r : board)
            std::cout << r << "\n";
        std::cout << "--------\n";
        return;
    }

    for (int col = 0; col < n; col++) {

        int d1 = row - col + (n - 1); //right to left
        int d2 = row + col; //left to right

        if (columns[col] || diag1[d1] || diag2[d2])
            continue;

        // DO
        board[row][col] = 'Q';
        columns[col] = diag1[d1] = diag2[d2] = true;

        solve(row + 1, board, columns, diag1, diag2, n);

        // UNDO
        board[row][col] = '.';
        columns[col] = diag1[d1] = diag2[d2] = false;
    }
}



//solve3 - return count
int solve3(int row,
          int n,
          vector<bool>& columns,
          vector<bool>& diag1,
          vector<bool>& diag2)
{
    // Base case: placed queens in all rows
    if (row == n)
        return 1;

    int count = 0;

    for (int col = 0; col < n; col++) {

        int d1 = row - col + (n - 1);
        int d2 = row + col;

        if (columns[col] || diag1[d1] || diag2[d2])
            continue;

        // DO
        columns[col] = diag1[d1] = diag2[d2] = true;

        count += solve(row + 1, n, columns, diag1, diag2);

        // UNDO
        columns[col] = diag1[d1] = diag2[d2] = false;
    }

    return count;
}


//return all n-queens boards
void backtrack(int row,
               int n,
               std::vector<std::string>& board,
               std::vector<bool>& columns,
               std::vector<bool>& diag1,
               std::vector<bool>& diag2,
               std::vector<vector<string>>& result)
{
    if (row == n) {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++) {

        int d1 = row - col + (n - 1);
        int d2 = row + col;

        if (columns[col] || diag1[d1] || diag2[d2])
            continue;

        // DO
        board[row][col] = 'Q';
        columns[col] = diag1[d1] = diag2[d2] = true;
//if (columns & (1 << col)) continue;
//bitmasks do this faster
        backtrack(row + 1, n, board, columns, diag1, diag2, result);

        // UNDO
        board[row][col] = '.';
        columns[col] = diag1[d1] = diag2[d2] = false;
    }
}
//What is the time complexity? O(N!)
//Why are there 2N − 1 diagonals?
//Space Complexity
//Recursion stack → O(N)
//Board storage → O(N²) per solution
//Result storage → O(S × N²)




int main()
{
    int n = 4;
    std::vector<std::string> board(n, std::string(n, '.'));

    solve(0, board, n);

    
    std::vector<std::string> board2(n, std::string(n, '.'));
    vector<bool> columns(n, false);
    vector<bool> diag1(2*n - 1, false);
    vector<bool> diag2(2*n - 1, false);
    //solve2(0, board, columns, diag1, diag2, n);

    backtrack(0, n, board, columns, diag1, diag2, result);

    
    return EXIT_SUCCESS;
}

