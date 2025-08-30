//Given a square matrix mat[][] of size n x n,
//where mat[i][j] == 1 means person i knows person j,
//and mat[i][j] == 0 means person i does not know person j, find the celebrity person where,
//
//A celebrity is defined as someone who:
//
//Is known by everyone else
//Does not know anyone (except themselves)

//mat[celebrity][j], = 0 for any j
//mat[i][celebrity] = 1 for any i

//Note: It is guaranteed that mat[i][i] == 1 for all i



//[Naive Approach] Using Adjacency List - O(n2) Time and O(n) Space
//Run a loop from 0 to n and find the id where the indegree is n and outdegree is 1.

/*#include <iostream>
#include <vector>

using namespace std;

int celebrity(vector<vector<int>> & mat) {
    int n = mat.size();

    // indegree and outdegree array
    vector<int> indegree(n, 0), outdegree(n, 0);

    // query for all edges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = mat[i][j];

            // set the degrees
            outdegree[i] += x;
            indegree[j] += x;
        }
    }

    // find a person with indegree n-1
    // and out degree 0
    for (int i = 0; i < n; i++)
        if (indegree[i] == n && outdegree[i] == 1)
            return i;

    return -1;
}

int main() {
    vector<vector<int> > mat = {{ 1, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 1 }};
    cout << celebrity(mat);
    return 0;
}*/



//[Better Approach] Using Stack - O(n) Time and O(n) Space
//Step by Step Implementation:
//
//Create a stack and push all the ids in the stack.
//Run a loop while there are more than 1 element in the stack.
//Pop the top two elements from the stack (represent them as A and B)
//If A knows B, then A can't be a celebrity and push B in the stack. Else if A doesn't know B, then B can't be a celebrity push A in the stack.
//Assign the remaining element in the stack as the celebrity.
//Run a loop from 0 to n-1 and find the count of persons who knows the celebrity and the number of people whom the celebrity knows.
//=> If the count of persons who knows the celebrity is n-1 and the count of people whom the celebrity knows is 0 then return the id of the celebrity else return -1.

/*
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int celebrity(vector<vector<int>> & mat) {
    int n = mat.size();
    stack<int> st;

    // push everybody in stack
    for (int i = 0; i < n; i++)
        st.push(i);

    // find a potential celebrity
    while (st.size() > 1) {

        int a = st.top();
        st.pop();

        int b = st.top();
        st.pop();

        // if a knows b
        if (mat[a][b]) {
            st.push(b);
        }
        else {
            st.push(a);
        }
    }

    // potential candidate of celebrity
    int c = st.top();
    st.pop();

    // Check if c is actually
    // a celebrity or not
    for (int i = 0; i < n; i++) {
        if(i == c) continue;

        // if any person doesn't
        // know 'c' or 'c' doesn't
        // know any person, return -1
        if (mat[c][i] || !mat[i][c])
            return -1;
    }

    return c;
}

int main() {
    vector<vector<int> > mat = {{ 1, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 1 }};
    cout << celebrity(mat);
    return 0;
}

*/





//[Expected Approach] Using Two Pointers - O(n) Time and O(1) Space

#include <iostream>
#include <vector>
using namespace std;

int celebrity(vector<vector<int>> & mat) {
    int n = mat.size();

    int i = 0, j = n - 1;
    while (i < j) {
        
        // j knows i, thus j can't be celebrity
        if (mat[j][i] == 1)
            j--;

        // else i can't be celebrity
        else
            i++;
    }

    // i points to our celebrity candidate
    int c = i;

    // check if c is actually
    // a celebrity or not
    for (i = 0; i < n; i++) {
        if(i == c) continue;

        // if any person doesn't
        // know 'c' or 'c' doesn't
        // know any person, return -1
        if (mat[c][i] || !mat[i][c])
            return -1;
    }

    return c;
}

int main() {
    vector<vector<int> > mat = {{ 1, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 1 }};
    cout << celebrity(mat);
    return 0;
}
