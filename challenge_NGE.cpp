// C++ implementation to find the next
// greater element using a stack
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextLargerElement(vector<int> &arr)
{
    int n = arr.size();
    stack<int> st;
    vector<int> res(n,-1);
    
    for(int i = n-1; i>=0; i--)
    {
        while(!st.empty() && st.top()<=arr[i])
        {
            st.pop();
        }
        
        if(!st.empty())
        {
            res[i] = st.top();
        }
        
        
        st.push(i);
        
    }
    //      -1 1 3 -1
    //stack  8
    return res;
}

int main() {

    vector<int> arr = {6, 8, 0, 1, 3};
    vector<int> res = nextLargerElement(arr);

    for (int x : res) {
        cout << x << " ";
    }

    return 0;
}


