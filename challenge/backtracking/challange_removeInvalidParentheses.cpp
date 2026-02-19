//Remove Invalid Parentheses
//Problem
//
//Given a string s containing:
//
//'('  ')'
//and letters
//
//
//Remove the minimum number of invalid parentheses to make the string valid.
//
//Return all possible valid results.
//
//Valid examples:
//
//()
//()()
//(a)()
//
//
//Invalid examples:
//
//(
//)
//)(
//(()

//
//Example 1
//
//Input:
//
//s = "()())()"
//
//
//Output:
//
//(())()
//()()()


#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>


//
// Step 1: Calculate minimum removals needed
//
std::pair<int,int> getRemovals(const std::string& s)
{
    int leftRem = 0;
    int rightRem = 0;

    for (char c : s)
    {
        if (c == '(')
        {
            leftRem++;
        }
        else if (c == ')')
        {
            if (leftRem > 0)
                leftRem--;
            else
                rightRem++;
        }
    }

    return {leftRem, rightRem};
}


//
// Step 2: Backtracking function
//
void solve(const std::string& s,
           int index,
           int leftRem,
           int rightRem,
           int balance,
           std::string current,
           std::unordered_set<std::string>& result)
{
    // Prune invalid state
    if (balance < 0)
        return;

    // Base case
    if (index == s.size())
    {
        if (leftRem == 0 && rightRem == 0 && balance == 0)
        {
            result.insert(current);
        }
        return;
    }

    char c = s[index];

    //
    // OPTION 1: Remove character
    //
    if (c == '(' && leftRem > 0)
    {
        solve(s,
              index + 1,
              leftRem - 1,
              rightRem,
              balance,
              current,
              result);
    }
    else if (c == ')' && rightRem > 0)
    {
        solve(s,
              index + 1,
              leftRem,
              rightRem - 1,
              balance,
              current,
              result);
    }


    //
    // OPTION 2: Keep character
    //

    // If letter, always keep
    if (c != '(' && c != ')')
    {
        solve(s,
              index + 1,
              leftRem,
              rightRem,
              balance,
              current + c,
              result);
    }
    else if (c == '(')
    {
        solve(s,
              index + 1,
              leftRem,
              rightRem,
              balance + 1,
              current + c,
              result);
    }
    else if (c == ')')
    {
        solve(s,
              index + 1,
              leftRem,
              rightRem,
              balance - 1,
              current + c,
              result);
    }
}



//
// Main function
//
int main()
{
    std::string s = "()())()";

    // Step 1: find removals needed
    std::pair<int,int> removals = getRemovals(s);

    int leftRem = removals.first;
    int rightRem = removals.second;

    std::unordered_set<std::string> resultSet;

    // Step 2: backtracking
    solve(s,0, leftRem, rightRem, 0, "", resultSet);


    // Convert to vector for output
    std::vector<std::string> result(resultSet.begin(), resultSet.end());


    // Print results
    std::cout << "Valid strings:\n";

    for (const std::string& str : result)
    {
        std::cout << str << "\n";
    }

    return EXIT_SUCCESS;
}
