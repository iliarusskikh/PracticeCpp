//O(4^N)
//Letter Combinations of Phone Number
//: mapping choices from a lookup table.

//Problem
//
//Given a string containing digits from 2-9, return all possible letter combinations the number could represent.
//
//Mapping is like a phone keypad:
//
//2 → abc
//3 → def
//4 → ghi
//5 → jkl
//6 → mno
//7 → pqrs
//8 → tuv
//9 → wxyz
//
//Example
//Input:
//digits = "23"
//
//Output:
//ad
//ae
//af
//bd
//be
//bf
//cd
//ce
//cf


//Try each possible letter
//Recurse to next digit
//Backtrack


#include <iostream>
#include <vector>

void solve(const std::string& digits, int index, std::string& current, std;:vector<std::string>& result, const std::vector<std::string>& mapping)
{
    // Base case
    if (index == digits.size())
    {
        result.push_back(current);
        return;
    }

    std::string letters = mapping[digits[index] - '0'];
//    digits[index] = '2'; digits = "23"
//    '2' - '0' = 2
//    mapping[2] = "abc"

    for (char letter : letters)
    {
        // choose
        current.push_back(letter);

        // recurse
        solve(digits, index + 1, current, result, mapping);

        // backtrack
        current.pop_back(); //proceed with next available letter for given digit
    }
}


int main()
{
    std::string digits = "23";

    std::vector<std::string> mapping =
    {
        "",
        "",      // 0,1 unused
        "abc",       // 2
        "def",       // 3
        "ghi",       // 4
        "jkl",       // 5
        "mno",       // 6
        "pqrs",      // 7
        "tuv",       // 8
        "wxyz"       // 9
    };

    std::vector<std::string> result;
    std::string current;

    solve(digits, 0, current, result, mapping);

    for (const string& s : result)
        cout << s << endl;

    return EXIT_SUCCESS;
}

