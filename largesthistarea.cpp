//Largest Rectangular Area in a Histogram

/*
#include <iostream>
#include <vector>

using namespace std;

int getMaxArea(vector<int> &hist){
    int res = 0, n = hist.size();
  
    // Consider every bar one by one
    for(int i = 0; i < n; i++){
        int curr = hist[i];
      
        // Traverse left while we have a greater height bar
        for(int j = i-1; j>=0 && hist[j] >= hist[i]; j--)
             curr += hist[i];
      
        // Traverse right while we have a greater height bar
        for(int j = i+1; j<n && hist[j] >= hist[i]; j++)
            curr += hist[i];
      
        res = max(res, curr);
    }
    return res;
}

int main()
{
    vector<int> hist =  {60, 20, 50, 40, 10, 50, 60};
    cout << getMaxArea(hist);
    return 0;
}
*/

#include <iostream>
#include <vector>

using namespace std;

int getMaxArea(vector<int>& arr) {
    int n = arr.size();
    stack<int> s;
    int res = 0;
    int tp, curr;
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && arr[s.top()] >= arr[i])
        {
            // The popped item is to be considered as the
            // smallest element of the histogram
            tp = s.top();
            s.pop();
          
            // For the popped item previous smaller element is
            // just below it in the stack (or current stack top)
            // and next smaller element is i
            int width = s.empty() ? i : i - s.top() - 1;
          
            res = max(res,  arr[tp] * width);
        }
        s.push(i);
    }

    // For the remaining items in the stack, next smaller does
    // not exist. Previous smaller is the item just below in
    // stack.
    while (!s.empty()) {
        tp = s.top();
        s.pop();
        curr = arr[tp] * (s.empty() ? n : n - s.top() - 1);
        res = max(res, curr);
    }

    return res;
}

int main() {
    vector<int> arr = {60, 20, 50, 40, 10, 50, 60};
    cout << getMaxArea(arr);
    return 0;
}


