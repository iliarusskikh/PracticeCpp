//Input: k = 3, arr[][] = [[1, 3, 5, 7], [2, 4, 6, 8], [0, 9, 10, 11]]
//Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

//[Naive Approach] Concatenate all and Sort O(n*log(n))
/*
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> mergeKArrays(vector<vector<int>>& arr, int k) {
    vector<int> res;

    // Append all arrays into res
    for (const auto& vec : arr) {
        for (int val : vec)
            res.push_back(val);
    }

    // Sort the res
    sort(res.begin(), res.end());

    return res;
}

// Driver's code
int main() {
    vector<vector<int>> arr = {{1, 3, 5, 7},
                              {2, 4, 6, 8},
                              {0, 9, 10, 11}};
                              
    int k = 3;
    vector<int> res = mergeKArrays(arr, k);

    // Print the array elements
    for (int val : res) {
        cout << val << " ";
    }

    return 0;
}
*/



//[Expected Approach 2] Using Min-Heap - Works better for Different Sized Arrays O(n*log(k)),
#include <iostream>
#include <queue>
#include <vector>

using namespace std;


vector<int> mergeKArrays(const vector<vector<int>> &arr, int K){
    
    vector<int> output;
    typedef pair<int, pair<int, int>> Pair

    // Min-heap: {value, {array index, element index}}
    priority_queue<Pair, vector<Pair>, greater<Pair>> minHeap;

    // Push first element of each array
    for (int i = 0; i < K; ++i){
        
        if (!arr[i].empty()){
            minHeap.push({arr[i][0], {i, 0}});
        }
    }

    // Merge all elements
    while (!minHeap.empty()){
        
        auto top = minHeap.top();
        minHeap.pop();

        int val = top.first;
        int i = top.second.first;
        int j = top.second.second;

        output.push_back(val);

        // Push next element from same array
        if (j + 1 < arr[i].size()){
            
            minHeap.push({arr[i][j + 1], {i, j + 1}});
        }
    }

    return output;
}

int main(){
    
    vector<vector<int>> arr = {{1, 3, 5, 7}, {2, 4, 6, 8}, {0, 9, 10, 11}};

    int K = arr.size();
    vector<int> result = mergeKArrays(arr, K);
    
    return 0;
}
