//Given a string str consisting only of lowercase letters and the characters '(' and ')'. Your task is to delete minimum parentheses so that the resulting string is balanced, i.e., every opening parenthesis has a matching closing parenthesis in the correct order, and no extra closing parentheses appear. Print all distinct strings you can obtain by performing the minimum number of removals.

//Input: str = "(v)())()"
//Output: "(v)()()"  "(v())()"
//Explanation: The given string is the modified version of first string containing a letter 'v' . As the letters do not differ the parentheses, the solution remains the same.
//
//Input: S = ")("
//Output: ""


//Using Breadth First Search - O(2 ^ n) Time and O(2 ^ n) Space
//The idea is to remove brackets one by one and check for balance. To remove brackets in a systematic way, we use BFS order.  We remove one bracket at a time, check for balance, then remove more brackets and again check in BFS manner.  We stop when we find a balanced string.
//One important observation about this problem is, we can check the balancing by simply counting opening and closing brackets because we have only one type of brackets. We do not need to use stack to check.
/*
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// method returns true if string
// contains valid parenthesis
bool isValidString(string str) {
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(')
            cnt++;
        else if (str[i] == ')')
            cnt--;
        if (cnt < 0)
            return false;
    }
    return (cnt == 0);
}

//  function to remove invalid parenthesis
vector<string> validParenthesis(string &str) {

    unordered_map<string, int> visit;    // to ignore already visited string
    queue<string> q;    //  queue to maintain BFS

    vector<string> res;    // to store the valid strings
    bool level = false;

    q.push(str);    //  pushing given string as starting node into queue
    
    visit[str] = 1;    // mark the string as visited

    // while queue is not empty
    while (!q.empty()) {
        string temp = q.front();
        q.pop();

        // check if the string is valid
        if (isValidString(temp)) {
            
            // if valid, store it
            res.push_back(temp);

            // make level true, so that valid string
            // of only that level are processed.
            level = true;
        }
        if (level)
            continue;

        for (int i = 0; i < temp.length(); i++) {

            // if current character is not a parenthesis
            // continue to next character
            if (temp[i] != '(' && temp[i] != ')')
                continue;

            // Removing parenthesis from str and
            // pushing into queue,if not visited already
            string cur = temp.substr(0, i) + temp.substr(i + 1);//removes one character, from 0 to i excluding, then from i+1 till the end
            if (visit.count(cur) == 0) {
                q.push(cur);
                visit[cur] = 1;
            }
        }
    }
    return res;
}

int main() {
    string str = "(v)())()";
    vector<string> res = validParenthesis(str);
    for (string s : res) {
        cout << s << endl;
    }
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

// Returns true if the string has balanced parentheses (only ( and ) matter)
bool isValid(const string& s) {
    int count = 0;
    for (char c : s) {
        if (c == '(')      ++count;
        else if (c == ')') --count;
        if (count < 0)     return false; //too many
    }
    return count == 0;
}

vector<string> removeInvalidParentheses(const string& s) {
    vector<string> result;
    if (s.empty()) {
        result.push_back("");
        return result;
    }

    unordered_set<string> visited;
    queue<string> q;

    q.push(s);
    visited.insert(s);

    bool found_valid_level = false;  // once true - we are at minimal removal level

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        // If valid = collect it (all at this level have same # of removals)
        if (isValid(current)) {
            result.push_back(current);
            found_valid_level = true;  // from now on we only collect from this level
        }

        // If we already found valid strings = don't generate worse (more removals)
        if (found_valid_level) {
            continue;
        }

        // Try removing one parenthesis at a time
        for (size_t i = 0; i < current.size(); ++i) {
            // Skip if not a parenthesis
            if (current[i] != '(' && current[i] != ')') {
                continue;
            }

            // Create new string by removing char at i
            string next = current;
            next.erase(i, 1);

            // Add only if not seen before
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }

    return result;
}

int main() {
    string input = "(v)())()";
    // string input = "()())()";   // classic example
    // string input = "(a)())()";

    vector<string> results = removeInvalidParentheses(input);

    cout << "Valid strings after minimal removals:\n";
    for (const string& res : results) {
        cout << res << "\n";
    }

    return 0;
}



/*
//Using Depth First Search - O(2 ^ n) Time and O(2 ^ n) Space
//We first determine how many opening ( and closing ) parentheses are invalid and need to be removed. Then, use a recursive function to explore all ways of removing these parentheses while maintaining balance between open and close brackets. At each step, either skip a parenthesis (if it's invalid) or include it in the current string (if it helps form a valid expression), and continue building the string. Only strings that end with no unmatched parentheses are collected as valid results.

using namespace std;

// Backtracking function
void dfs(const string& s, int start, int balance, int left_to_remove, int right_to_remove,
         string current, unordered_set<string>& result) {

    if (start == s.size()) {
        // We only accept if fully balanced and removed exactly the required number
        if (balance == 0 && left_to_remove == 0 && right_to_remove == 0) {
            result.insert(current);
        }
        return;
    }

    char c = s[start];

    // Case 1: current char is not parenthesis → must keep it
    if (c != '(' && c != ')') {
        dfs(s, start + 1, balance, left_to_remove, right_to_remove,
            current + c, result);
        return;
    }

    // Case 2: '('
    if (c == '(') {
        // Option A: remove it (if we still need to remove left parentheses)
        if (left_to_remove > 0) {
            dfs(s, start + 1, balance, left_to_remove - 1, right_to_remove,
                current, result);
        }

        // Option B: keep it (always safe — increases balance)
        dfs(s, start + 1, balance + 1, left_to_remove, right_to_remove,
            current + c, result);
    }
    // Case 3: ')'
    else {  // c == ')'
        // Option A: remove it (if we still need to remove right parentheses)
        if (right_to_remove > 0) {
            dfs(s, start + 1, balance, left_to_remove, right_to_remove - 1,
                current, result);
        }

        // Option B: keep it — but only if it won't make balance negative
        if (balance > 0) {
            dfs(s, start + 1, balance - 1, left_to_remove, right_to_remove,
                current + c, result);
        }
        // Note: if balance == 0, we **cannot** keep this ')' — it would go negative
    }
}

// Main function: count how many to remove, then start DFS
vector<string> removeInvalidParentheses(string s) {
    unordered_set<string> result;

    // Step 1: count how many ( and ) we need to remove
    int left_to_remove = 0;   // excess '('
    int right_to_remove = 0;  // excess ')'
    int balance = 0;

    for (char c : s) {
        if (c == '(') {
            ++balance;
            ++left_to_remove;  // tentatively count all as removable
        } else if (c == ')') {
            if (balance > 0) {
                --balance;
                --left_to_remove;  // this ) matches a previous (, so not excess
            } else {
                ++right_to_remove; // unmatched ), must remove
            }
        }
    }
    // Now left_to_remove = number of excess '(' that must be removed

    // Step 2: start backtracking
    dfs(s, 0, 0, left_to_remove, right_to_remove, "", result);

    return {result.begin(), result.end()};
}

int main() {
    string input = "(v)())()";
    // string input = "()())()";        // → "()()"
    // string input = ")(()";           // → "()"
    // string input = "(()";            // → "((" or "()" depending on removal

    vector<string> res = removeInvalidParentheses(input);

    cout << "Valid strings after minimal removals:\n";
    for (const string& r : res) {
        cout << r << "\n";
    }

    return 0;
}
*/
