//[Approach 2] Without using Stack - O(n) Time and O(1) Space

//Instead of using an external stack, we can simulate stack operations directly on the input string by modifying it in place. A variable top is used to track the index of the last unmatched opening bracket. Whenever an opening bracket is found, it is placed at the next top position. For a closing bracket, we check if it matches the character at top. If it does, we simply decrement top; otherwise, the string is unbalanced. In the end, if top is -1, all brackets are matched and the string is balanced.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isBalanced(string& s) {
    
    // stack top index in string
    int top = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            
            // push opening bracket
            s[++top] = s[i];
        }
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            
            // no opening bracket
            if (top == -1) return false;
            if ((s[i] == ')' && s[top] != '(') ||
                (s[i] == '}' && s[top] != '{') ||
                (s[i] == ']' && s[top] != '[')) {
                return false;
            }
            top--;
        }
    }
    
    // balanced if stack empty
    return top == -1;
}

int main() {
      string s="[()()]{}";
      cout<<(isBalanced(s)?"true":"false");
}
