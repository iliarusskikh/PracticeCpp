//Sort a Stack using Recursion
//Time Complexity: O(n^2).
//Auxiliary Space: O(n) due to call stack and temporary stack.


#include <iostream>
#include <stack>
using namespace std;

void sortedInsert(stack<int> &s, int x) {
    if (s.empty() || x > s.top()) {
        s.push(x);
        return;
    }
    int temp = s.top();
    s.pop(); //remove other elements
    sortedInsert(s, x); //try to settle X element
    s.push(temp);//push it back, as X found its position
}

void sort(stack<int> &s) {
    if (!s.empty()) {
        int x = s.top();
        s.pop();
        sort(s);
        sortedInsert(s, x);
    }
}

int main() {
    stack<int> s;

    s.push(11);
    s.push(2);
    s.push(32);
    s.push(3);
    s.push(41);

    sort(s);

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
