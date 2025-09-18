//Input: s = "geeksforgeeks"
//Output: e
//Explanation: e is the first element that repeats
//
//Calculate all frequencies of all characters using Counter() function.
//Traverse the string and check if any element has frequency greater than 1.
//Print the character and break the  loop

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Function which repeats
// first repeating character
void printrepeated(string str)
{

    // Calculating frequencies
    // using unordered_map
    unordered_map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }

    // Traverse the string
    for (char c : str) {
        if (freq[c] > 1) {
            cout << c << endl;
            break;
        }
    }
}

// Driver code
int main()
{
    string str = "geeksforgeeks";

    // passing string to printrepeated function
    printrepeated(str);

    return 0;
}
