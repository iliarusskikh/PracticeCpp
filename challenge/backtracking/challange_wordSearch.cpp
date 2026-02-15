//Word Search
//Given: 2D grid of characters; A word

//true  → if the word exists in the grid
//false → otherwise

//You cannot reuse the same cell in one path
//move up down left right cell

//Then recursively check neighbors.

//O(rows × cols × 4^L)

//start from every positon
//within this iteration, send recursion in 4 directions to match the word
//before each recursion mark as visited board element
//backtrack - UNDO after recursion

#include <iostream>
#include <vector>
#include <string>



class Solution{
public:

    bool dfs(std::vector<std::vector<char>>& board, std::string& word, int row, int col, int index)
    {
        // Base case: entire word found
        if (index == word.length())
            return true;

        // Bounds check
        if (row < 0 || col < 0 ||
            row >= board.size() ||
            col >= board[0].size())
            return false;

        // Letter mismatch - elimitate visited
        if (board[row][col] != word[index])
            return false;

        // Mark visited (DO)
        char temp = board[row][col];
        board[row][col] = '#';

        // Explore 4 directions
        bool found =
            dfs(board, word, row+1, col, index+1) ||
            dfs(board, word, row-1, col, index+1) ||
            dfs(board, word, row, col+1, index+1) ||
            dfs(board, word, row, col-1, index+1);

        // Undo visited (BACKTRACK)
        board[row][col] = temp;

        return found;
    }


    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int rows = board.size();
        int cols = board[0].size();

        // Try starting from every cell
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (dfs(board, word, r, c, 0))
                    return true;
            }
        }

        return false;
    }

};



int main() {
    std::vector<std::vector<char>> board =
    {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    Solution sol;

    std::string myWord = "ABCCED";
    std::cout << sol.exist(board, myWord) << "\n"; // 1 (true)
    
    
    
    return EXIT_SUCCESS;
}


