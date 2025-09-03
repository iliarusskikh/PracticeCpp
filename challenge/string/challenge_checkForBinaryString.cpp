//Given a string s, the task is to check if it is a binary string or not. A binary string is a string which only contains the characters '0' and '1'.

//Input: s = "01010101010"
//Output: true
//
//Input: s = "geeks101"
//Output: false

// C++ Program to check if a string is
// binary string or not

#include <iostream>
using namespace std;

bool isBinary(string &s) {
    for (int i = 0; i < s.length(); i++) {

        // Check if the character is neither
        // '0' nor '1'
        if (s[i] != '0' && s[i] != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    string s = "01010101010";
    cout << (isBinary(s) ? "true" : "false");
    return 0;
}
