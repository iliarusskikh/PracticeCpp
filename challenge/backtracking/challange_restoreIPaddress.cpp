//Restore IP Addresses
//Problem

//Given a string containing only digits, return all possible valid IP addresses that can be formed by inserting dots into the string.

//An IP address consists of 4 numbers, each between:
//0 and 255 inclusive

//Rules:
//Exactly 4 parts
//Each part must be 0–255
//No leading zeros allowed


//Example 1
//
//Input:
//
//s = "25525511135"
//
//
//Output:
//
//255.255.11.135
//255.255.111.35


#include <iostream>
#include <vector>

bool isValid(const std::string& s, int start, int end)
{
    int length = end - start + 1;

    if (length > 3)
        return false;

    if (s[start] == '0' && length > 1)
        return false;

    int num = std::stoi(s.substr(start, length));

    return num <= 255;
}



void solve(const std::string& s, int start, int parts, std::string current, std::vector<std::string>& result)
{
    // If 4 parts formed and string consumed
    if (parts == 4 && start == s.size())
    {
        current.pop_back(); // remove last dot
        result.push_back(current);
        return;
    }

    // Pruning
    if (parts == 4 || start == s.size())
        return;

    for (int end = start; end < s.size() && end < start + 3; end++)
    {
        if (isValid(s, start, end))
        {
            std::string segment = s.substr(start, end - start + 1);

            solve(s, end + 1, parts + 1, current + segment + ".", result);
        }
    }
}


int main()
{
    std::string s = "25525511135";

    std::vector<std::string> result;

    solve(s, 0, 0, "", result);

    for (const std::string& ip : result)
        std::cout << ip << "\n";

    return EXIT_SUCCESS;
}

