//Find if a given string can be represented from a substring by iterating the substring “n” times
//Input: str = "abcabcabc"
//Output: true
//The given string is 3 times repetition of "abc"
//
//Approach:
//
//Initially set first pointer - i at 0th index of given string and second pointer - j at 1st index.
//check the characters at both index. if both matches, take period as (j-i) and increment i and j.
//if doesn't match, Once again check if current character matches with first character at 0th index. if matches, update period as j(j-0=j) and set i to next character.
//f both characters not matches, set i to 0 and update period to -1.
//At the end check if the calculated period exactly divides the length of the string. if not, update period to -1. This check eliminates the presence of strings ending with suffix less than the period. for e.g period for the string "GEEKSFORGEEKS" is calculated as 8 but the suffix string(GEEKS) is having 5 characters only and is incomplete.


using namespace std;

int findPeriod(string A)
{
    int length = A.size();

    // Initially consider there is no period for given String
    int period = -1;

    /*set two pointers one(i) at index 0 and other(j) at index 1. increment j till first character is obtained in the string*/
    int i = 0;
    for (int j = 1; j < length; j++) {
        int currChar = A[j];
        int comparator = A[i];

        /*If current character matches with first character update period as the difference of j and i*/
        if (currChar == comparator) {
            period = (j - i);
            i++;
        }

        /* if any mismatch occurs in between set i to
         * zero also check if current character again
         * matches
         * with starting character. If matches, update
         * period*/
        else {
            if (currChar == A[0]) {
                i = 1;
                period = j;
            }
            else {
                i = 0;
                period = -1;
            }
        }
    }

    /*check if the period is exactly dividing
     * string if not reset the period to -1
     * this eliminates partial substrings like
     * e.g string -"GEEKSFORGEEKS" */

    period = (length % period != 0) ? -1 : period;
    return period;
}

int main()
{
    vector<string> testStrings
        = { "ABCABC",        "ABABAB",   "ABCDABCD",
            "GEEKSFORGEEKS", "GEEKGEEK", "AAAACAAAAC",
            "ABCDABC" };
    int n = testStrings.size();
    for (int i = 0; i < n; i++) {
        if (findPeriod(testStrings[i]) == -1)
            cout << "false\n";
        else
            cout << "True\n";
    }

    return 0;
}

    // This code is contributed by rakeshsahni
