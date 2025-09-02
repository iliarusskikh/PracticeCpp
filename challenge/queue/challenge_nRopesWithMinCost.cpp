//Given an array arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost. The cost to connect two ropes is the sum of their lengths.
//
//Input: arr[] = [4, 3, 2, 6]
//Output: 29
//Explanation: We can connect the ropes in following ways.
//1) First connect ropes of lengths 2 and 3. Which makes the array [4, 5, 6]. Cost of this operation 2 + 3 = 5.
//2) Now connect ropes of lengths 4 and 5. Which makes the array [9, 6]. Cost of this operation 4 + 5 = 9.
//3) Finally connect the two ropes and all ropes have connected. Cost of this operation 9 + 6 =15. Total cost is 5 + 9 + 15 = 29. This is the optimized cost for connecting ropes.



//[Naive Approach] Greedy with Repeated Sorting - O(n^2*log(n)) Time and O(n) Space
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to return the minimum cost of connecting the ropes.
int minCost(vector<int>& arr) {
    int totalCost = 0;
    while (arr.size() > 1) {
        sort(arr.begin(), arr.end());
        int first = arr[0];
        int second = arr[1];
        arr.erase(arr.begin());
        arr.erase(arr.begin());
        int cost = first + second;
        totalCost += cost;
        arr.push_back(cost);
    }
    return totalCost;
}

int main() {
    vector<int> ropes = {4, 3, 2, 6};
    cout << minCost(ropes) << endl;
    return 0;
}*/




//[Expected Approach] Greedy with Heap - O(n*log(n)) Time and O(n) Space

#include <bits/stdc++.h>
using namespace std;

int minCost(vector<int> &arr) {

    // Create a priority queue
    // By default 'less' is used which is for decreasing
    // order and 'greater' is used for increasing order
    priority_queue<int, vector<int>,
               greater<int>> pq(arr.begin(), arr.end());

    // Initialize result
    int res = 0;

    // While size of priority queue is more than 1
    while (pq.size() > 1) {

        // Extract shortest two ropes from pq
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        // Connect the ropes: update result and
        // insert the new rope to pq
        res += first + second;
        pq.push(first + second);
    }

    return res;
}

int main() {

    vector<int> arr = {4, 3, 2, 6};
    cout << minCost(arr);
    return 0;
}
