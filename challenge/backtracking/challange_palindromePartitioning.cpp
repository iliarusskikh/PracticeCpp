//O(N * 2^N)

// Given a string s, partition it such that every substring of the partition is a palindrome.
// Return all possible palindrome partitionings of s

//input: s = "aab"
//[
//["a", "a", "b"],
//["aa", "b"]
//]

//Core Backtracking Idea
//At each index:
//Try every possible substring starting at that index.
//If substring is palindrome:
//choose it
//recurse
//backtrack

#include <iostream>
#include <vector>
#include <string>


bool isPalindrome(string& s, int left, int right) //start end
{
    while (left < right)
    {
        if (s[left] != s[right])
            return false;
        left++;
        right--;
    }
    return true;
}



void solve(std::string& s, int start, std::vector<std::string>& current, std::vector<std::vector<std::string>>& result)
{
    // Base case
    if (start == s.size())
    {
        result.push_back(current);
        return;
    }

    for (int end = start; end < s.size(); end++)
    {
        if (isPalindrome(s, start, end))
        {
            // choose
            current.push_back(s.substr(start, end - start + 1));

            // Each recursion level must preserve its own start.
            solve(s, end + 1, current, result); //keep accumulating current variable, then push it into results

            // backtrack
            current.pop_back();
        }
    }
}


int main()
{
    std::string s = "aaba";

    std::vector<std::vector<std::string>> result;
    std::vector<std::string> current;

    solve(s, 0, current, result);

    // print result
    for (auto& partition : result)
    {
        for (auto& str : partition)
            cout << str << " ";
        cout << "\n";
    }

    return EXIT_SUCCESS;
}
//  a a b
// aa b
