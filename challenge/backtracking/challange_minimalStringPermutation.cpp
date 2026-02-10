#include <iostream>
#include <vector>


void permutee(int pos, std::string& s, std::vector<bool>& used, std::string& current) {
    //base case - return when entire string completed
    if (pos == s.length()) {
        std::cout << "Base case: " << current << "\n";
        return 1;
    }

    
    unordered_set<char> tried; // characters tried at this depth
    int count = 0; //count permutations

    
    
    for (int i = 0; i < s.length(); i++) {
        if (used[i]) continue;   // constraint - so that in recursion this initial index is frozen.
        if (tried.count(s[i])) continue; // skip duplicate choice

        used[i] = true;          // make choice DO
        current.push_back(s[i]); //this letter of s[i] has been used!
        std::cout << "Before Permute: " << current << "\n";
        
        count += permutee(pos + 1, s, used, current);

        // backtrac
        used[i] = false;
        current.pop_back(); // and pop 3nd
        std::cout << "After Permute: " << current << "\n";
    }
    
    return count;
}


void permute_advanced(int pos, std::string& s) {
    if (pos == s.length()) {
        std::cout << s << "\n";
        return;
    }

    for (int i = pos; i < s.length(); i++) {
        std::swap(s[pos], s[i]);     // make choice
        std::cout << "Before Permute i, pos: " << i << " "<< pos <<"\n";

        permute_advanced(pos + 1, s);    // recurse
        std::cout << "After Permute i, pos: " << i << " "<< pos <<"\n";

        std::swap(s[pos], s[i]);     // backtrack
    }
}



int main() {
    std::string s = "ABC";
    std::vector<bool> used(s.length(), false); //vector to store reserved elements
    std::string current; //current permutated string creation

    std::cout << permuteCount(0, s, used) << "\n"; // 6

    permute_advanced(0,s);
    
    
    return EXIT_SUCCESS;
}

