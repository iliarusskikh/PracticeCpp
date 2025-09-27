//C++ Program to Check if a Given String is Palindrome or Not

//A string is said to be palindrome if the reverse of the string is the same as the original string. In this article, we will check whether the given string is palindrome or not in C++.


//Input: str = "ABCDCBA"
//Output: "ABCDCBA" is palindrome
//Explanation: Reverse of the string str is "ABCDCBA". So, it is palindrome.

//Using Two Pointer Method

// C++ program to check whether the string
// is palindrome or not using loop
#include <bits/stdc++.h>
using namespace std;

void isPalindrome (string str) {
  
      // Specify the starting and ending indexes
    int left = 0, right = str.size() - 1;
  
      // Flag to terminate the loop if mismatch
      // characters found
      bool flag = true;
      
      // Till the left is less than right
    while (left < right) {

        // If any character not match, break the
        // loop, string is not palindrome
        if (str[left] != str[right]) {
            flag = false;
            break;
        }
        left++;
        right--;
    }
      
      if (flag)
        cout << "\"" << str
          << "\" is palindrome." << endl;
          
    else
        cout << "\"" << str
          << "\" is NOT palindrome." << endl;
}
  

int main() {
  
      // Checking if given strings are palindrome
      isPalindrome("ABCDCBA");
    isPalindrome("ABCD");
    return 0;
}



/*
 
 // Recursive helper function to check if the string
 // is a palindrome
 bool palinHelper(const string& str, int left,
                  int right) {

     // If the start and end pointers cross each other,
       // it means all characters have matched
     if (left >= right)
         return true;

     // If characters don't match, the string is not
       // a palindrome
     if (str[left] != str[right])
         return false;

     // Recursively check for the rest of the string
     return palinHelper(str, left + 1, right - 1);
 }

 // Function to check if the string is a palindrome
 void isPalindrome(string str) {

     // Calling the recursive function to check
       // palindrome string
     if (palinHelper(str, 0, str.length() - 1))
         cout << "\"" << str << "\" is palindrome."
               << endl;
     else
         cout << "\"" << str << "\" is NOT palindrome."
               << endl;
 }
 */
