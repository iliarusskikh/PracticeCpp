//Multiply Large Numbers represented as Strings

//Given two numbers as strings s1 and s2, calculate their product.
//Note: The numbers can be negative. There can be zeros in the beginning of the numbers.

//Input: s1 = "0033", s2 = "2"
//Output: "66"
//Explanation: 33 * 2 = 66
//
//Input: s1 = "11", s2 = "23"
//Output: "253"
//Explanation: 11 * 23  = 253
//
//Input: s1 = "123", s2 = "0"
//Output: "0"
//Explanation: Anything multiplied by 0 is equal to 0.


//Approach: Using String Manipulation - (m * n) Time and O(m + n) Space
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string multiplyStrings(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    // check if string are negative
    int nn = 1, mm = 1;
    if (s1[0] == '-')
        nn = -1;
    if (s2[0] == '-')
        mm = -1;

    int isNeg = nn * mm;

    // will keep the result number in vector in reverse order
    vector<int> result(n1 + n2, 0);

    // index by s1
    int i1 = 0;

    // index by s2
    int i2 = 0;

    // go from right to left by s1
    for (int i = n1 - 1; i >= 0; i--) {
        if (s1[i] == '-')
            continue;
        int carry = 0;
        int n1 = s1[i] - '0';
        i2 = 0;

        // go from right to left by s2
        for (int j = n2 - 1; j >= 0; j--) {
            if (s2[j] == '-')
                continue;
            int n2 = s2[j] - '0';
            
            // multiply and add this result to the existing result
            int sum = n1 * n2 + result[i1 + i2] + carry;

            carry = sum / 10; // carry for next iteration

            result[i1 + i2] = sum % 10; // store result

            i2++;
        }

        if (carry > 0)// store carry in next cell
            result[i1 + i2] += carry;

        i1++;
    }

    int i = result.size() - 1;    // ignore '0's from the right
    while (i >= 0 && result[i] == 0)
        i--;

    // if all were '0's - means either both or one of s1 or s2 were '0'
    if (i == -1)
        return "0";

    string s = "";    // generate the result string

    while (i >= 0)
    s += to_string(result[i--]);

    // if negative
    if (isNeg == -1)
        s = "-" + s;

    return s;
}

int main() {
    string s1 = "0033", s2 = "2";
    cout << multiplyStrings(s1, s2);
    return 0;
}
