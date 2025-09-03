//Given two strings txt and pat, the task is to find if pat is a substring of txt. If yes, return the index of the first occurrence, else return -1.

//Using nested loops - O(m*n) Time and O(1) Space

// C++ program to check if a string is substring of other
// using nested loops

/*
#include <iostream>
using namespace std;

// Function to find if pat is a substring of txt
int findSubstring(string &txt, string &pat) {
    int n = txt.length();
    int m = pat.length();

    // Iterate through txt
    for (int i = 0; i <= n - m; i++) {

        // Check for substring match
        int j;
        for (j = 0; j < m; j++) {

            // Mismatch found
            if (txt[i + j] != pat[j]) {
                break;
            }
        }

        // If we completed the inner loop, we found a match
        if (j == m) {

            // Return starting index
            return i;
        }
    }
    
    // No match found
    return -1;
}

int main() {
    string txt = "geeksforgeeks";
    string pat = "eks";
    cout << findSubstring(txt, pat);

    return 0;
}

*/


//Using in-built library functions

#include <iostream>
using namespace std;

int main() {
    string txt = "geeksforgeeks";
    string pat = "eks";
    
    // If pat is found, returns the index of first
    // occurrence of pat. Otherwise, returns a special
    // constant value std::string::npos
    size_t idx = txt.find(pat);
  
    if(idx != string::npos)
        cout << idx;
    else
        cout << -1;

    return 0;
}
