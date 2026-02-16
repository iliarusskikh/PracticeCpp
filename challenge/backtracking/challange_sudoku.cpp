//You are given a partially filled 9 × 9 Sudoku board.
//
//Your task is to fill the board so that:
//
//Rules
//
//Each row must contain digits 1–9 exactly once
//
//Each column must contain digits 1–9 exactly once
//
//Each 3×3 subgrid must contain digits 1–9 exactly once
//
//Empty cells are represented by '.'
//
//You must modify the board in-place.

//input:
//5 3 . | . 7 . | . . .
//6 . . | 1 9 5 | . . .
//. 9 8 | . . . | . 6 .
//------+-------+------
//8 . . | . 6 . | . . 3
//4 . . | 8 . 3 | . . 1
//7 . . | . 2 . | . . 6
//------+-------+------
//. 6 . | . . . | 2 8 .
//. . . | 4 1 9 | . . 5
//. . . | . 8 . | . 7 9

//output:
//5 3 4 | 6 7 8 | 9 1 2
//6 7 2 | 1 9 5 | 3 4 8
//1 9 8 | 3 4 2 | 5 6 7
//------+-------+------
//8 5 9 | 7 6 1 | 4 2 3
//4 2 6 | 8 5 3 | 7 9 1
//7 1 3 | 9 2 4 | 8 5 6
//------+-------+------
//9 6 1 | 5 3 7 | 2 8 4
//2 8 7 | 4 1 9 | 6 3 5
//3 4 5 | 2 8 6 | 1 7 9


//Find empty cell
//Try digits 1–9
//Check if safe
//Place digit
//Recurse
//Undo if needed

//O(9^(empty_cells))

#include <iostream>
#include <vector>


class Solution {
public:

    bool isSafe(std::vector<std::vector<char>>& board,
                int row,
                int col,
                char num)
    {
        // Check row
        for (int c = 0; c < 9; c++)
            if (board[row][c] == num)
                return false;

        // Check column
        for (int r = 0; r < 9; r++)
            if (board[r][col] == num)
                return false;

        // Check 3x3 box
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;

        for (int r = startRow; r < startRow + 3; r++)
            for (int c = startCol; c < startCol + 3; c++)
                if (board[r][c] == num)
                    return false;

        return true;
    }


    bool solve(std::vector<std::vector<char>>& board)
    {
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                if (board[row][col] == '.') //looking for an empty cell
                {
                    for (char num = '1'; num <= '9'; num++) //try to insert a number in an empty cell
                    {
                        if (isSafe(board, row, col, num))
                        {
                            //same as m-colors approach..
                            board[row][col] = num;

                            if (solve(board))
                                return true;

                            board[row][col] = '.'; // backtrack
                        }
                    }

                    return false; // no digit fits the cell, proceed with backtracking..
                }
            }
        }

        return true;
    }


    void solveSudoku(std::vector<std::vector<char>>& board)
    {
        solve(board);
    }
};




int main()
{
    std::vector<std::vector<char>> board =
    {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},

        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},

        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    Solution sol; //create a solution instance

    sol.solveSudoku(board); //pass the board to solver

    std::cout << "Solved Sudoku:\n\n";

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            std::cout << board[row][col] << " ";
        }
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
