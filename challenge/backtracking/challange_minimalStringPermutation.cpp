//A depth-first search over a decision tree where we incrementally build a candidate solution and abandon (“backtrack”) as soon as we detect it cannot lead to a valid solution.
//Key components:
//
//State
//
//Choices
//
//Constraints
//
//Goal / Base case
//
//Undo (restore state)



//2. Why Backtracking Is Used
//
//Backtracking is used when:
//The problem is about searching for all or some valid configurations
//The solution must satisfy constraints
//The search space is combinatorial (exponential)
//It is especially useful when:
//You cannot directly compute the answer
//You must try combinations
//Constraints allow pruning early

//3. When Do We Use Backtracking?
//1) Combinatorial generation
//Permutations
//Combinations
//Subsets
//Binary strings
//k-length sequences
//2) Constraint Satisfaction Problems (CSP)
//N-Queens
//Sudoku
//Graph coloring
//Crossword puzzles
//Knight’s tour
//3) Decision problems
//Does a subset sum to target?
//Can we partition the set?
//Is there a path in a maze?
//Word search in a grid?


/*
 
 void backtrack(State& state) {

     if (is_solution(state)) {
         process(state);
         return;
     }

     for (Choice c : available_choices(state)) {

         if (!is_valid(c, state)) continue; // pruning

         make_choice(state, c);   // DO

         backtrack(state);

         undo_choice(state, c);   // UNDO
     }
 }
  */
//
//Backtracking is usually exponential:
//
//Permutations → O(n!)
//
//Subsets → O(2^n)
//
//N-Queens → roughly O(N!)
//
//But pruning can make it dramatically faster in practice.
//
//Worst-case exponential, average case often manageable.

//“Generate all…”
//“Find all possible…”
//“Return every configuration…”
//“Does there exist a solution…?”
//“Count the number of ways…”


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

        tried.insert(s[i]);      // mark this character as tried at this depth
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
        std::cout << "Swap: " << s[pos] << " "<< s[i] <<"\n";
        std::swap(s[pos], s[i]);     // make choice
        std::cout << "Before Permute i: " << i << " , pos:"<< pos <<"\n";
        

        permute_advanced(pos + 1, s);    // recurse
        std::cout << "After Permute i: " << i << " , pos:"<< pos <<"\n";
        std::cout << "Unswap: " << s[pos] << " "<< s[i] <<"\n";

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

