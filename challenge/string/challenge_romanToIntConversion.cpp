//Roman to Integer Conversion

//
//Given a string s representing a Roman numeral, find it's corresponding integer value.
//Roman numerals are formed using the following symbols: I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, and M = 1000.


//How does the conversion work?
//
//If a smaller value symbol comes before, we subtract. Otherwise, we add.
//In IV, I comes before V and V has a larger value 5. So our result is 5 - 1 = 4.
//In VI, V comes before I and I has a smaller value 1. So our result is 5 + 1 = 6.
//In II, we have same values, so we add and get 1 + 1 = 2
//In case of more than 2 characters, we traverse from left to right and group only when we see a greater value character after a smaller value character. For example MXVII is 1000 + 10 + 5 + 1 + 1 = 1017. And XLVII is (50 - 10) + 5 + 1 + 1 = 47. Note that L is larger and comes after X.

//[Expected Approach 1] Using Iterative Comparison - O(n) time and O(1) space

#include <iostream>
using namespace std;

// this function returns value of a Roman symbol
int value(char r) {
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;
    return -1;
}

// returns decimal value of roman numeral
int romanToDecimal(string& s) {
    int res = 0;

    for (int i = 0; i < s.length(); i++) {
        
        // get value of current symbol
        int s1 = value(s[i]);

        // Compare with the next symbol if it exists
        if (i + 1 < s.length()) {
            int s2 = value(s[i + 1]);

            // if current value is greater or equal,
            // add it to result
            if (s1 >= s2) {
                res += s1;
            }
            else {
                // else, add the difference and skip
                // next symbol
                res += (s2 - s1);
                i++;
            }
        }
        else {
            res += s1;
        }
    }

    return res;
}

int main() {
    string s = "IX";
    cout << romanToDecimal(s) << endl;
    return 0;
}



//[Expected Approach 2] Using Hashing - O(n) time and O(1) space
/*#include <iostream>
 #include <unordered_map>
 using namespace std;

 int romanToDecimal(string &s) {
     unordered_map<char, int> romanMap = {{'I', 1},
                                          {'V', 5},
                                          {'X', 10},
                                          {'L', 50},
                                          {'C', 100},
                                          {'D', 500},
                                          {'M', 1000}};

     int res = 0;
     for (int i = 0; i < s.length(); i++) {

         // if the current value is less than the next value,
         // subtract current from next and add to res
         if (i + 1 < s.length() && romanMap[s[i]] < romanMap[s[i + 1]]) {
             res += romanMap[s[i + 1]] - romanMap[s[i]];

             // skip the next symbol
             i++;
         }
         else {

             // otherwise, add the current value to res
             res += romanMap[s[i]];
         }
     }

     return res;
 }

 int main() {

     string s = "IX";
     cout << romanToDecimal(s) << endl;
     return 0;
 }*/
