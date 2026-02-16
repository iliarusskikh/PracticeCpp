//Given an integer n, generate all combinations of well-formed parentheses using exactly n pairs.
//Return the result as a vector of strings.

//Rule 1: Cannot use more than n open brackets
//Rule 2: Cannot close more than opened

//Backtracking with multiple constraints

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:

    void backtrack(std::vector<std::string>& result, std::string& current, int open, int close, int n)
    {
        // Base case: valid complete string
        if (current.length() == 2 * n)
        {
            result.push_back(current);
            return;
        }

        // Try adding '('
        if (open < n)
        {
            current.push_back('(');      // DO
            backtrack(result, current, open + 1, close, n);
            current.pop_back();         // UNDO
        }

        // Try adding ')'
        if (close < open)
        {
            current.push_back(')');     // DO
            backtrack(result, current, open, close + 1, n);
            current.pop_back();         // UNDO
        }
    }


    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> result;
        std::string current;

        backtrack(result, current, 0, 0, n);

        return result;
    }
};



int main()
{
    Solution sol;
    
    std::vector<std::string> result = sol.generateParenthesis(3); //3 pairs of par.
    
    for (auto& s : result)
        std::cout << s << "\n";
    
    return EXIT_SUCCESS;
}
