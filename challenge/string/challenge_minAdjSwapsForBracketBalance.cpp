//Min Adjacent Swaps for Bracket Balancing

//Given a string s of length 2n containing exactly n '[' and n ']' brackets. Find the minimum number of adjacent swaps needed to make the string balanced.

//Given a string s of length 2n containing exactly n '[' and n ']' brackets. Find the minimum number of adjacent swaps needed to make the string balanced.

//adjecent swaps!!


//[Expected Approach] Imbalance Counting Method - O(n) Time and O(1) Space
//We traverse the string from left to right while keeping track of how many [ and ] we have seen. Whenever the number of ] becomes greater than [, we say there is an imbalance. Later, when we encounter a [, if imbalance > 0, it means this [ must be shifted left to balance one of the earlier unmatched ]. The number of swaps needed is exactly equal to the current imbalance, so we add it to our total swap count and decrease the imbalance by 1. By the end of the scan, the accumulated count gives the minimum adjacent swaps required.


#include <iostream>
#include <string>
using namespace std;

int  swapCount(string &s) {
    int countLeft = 0, countRight = 0;
    
    // swap stores the number of swaps
    // required imbalance maintains
    int swap = 0 , imbalance = 0;
     
    for(int i = 0; i < s.length(); i++){
        if (s[i] == '['){
            countLeft++;
            if (imbalance > 0){
                
                // swaps count is last swap count + total
                // number imbalanced brackets
                swap += imbalance;
                
                // imbalance decremented by 1 as it solved
                // only one imbalance of Left and Right
                imbalance--;
            }
        }
        else if(s[i] == ']' ){
            countRight++;
            
            // imbalance is reset to current difference
            // between Left and Right brackets
            imbalance = (countRight - countLeft);
        }
    }
    return swap;
}
int main(){
    string s = "[]][][";
    cout << swapCount(s) << endl;
    return 0;
}
