#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to find the maximum element in each sliding
// window of size k
vector<int> maxSlidingWindow(vector<int>& arr, int k)
{
    vector<int> ans;
    priority_queue<pair<int,int>> pq;
    
    //initialise with the first k elements
    for(int i =0; i <k; ++i)
    {
        pq.push({arr[i],i});
    }
    
    ans.push_back(pq.top().first);
    
    for(int i =k; i<arr.size(); ++i)
    {
        pq.push({arr[i],i});
        while(pq.top().second < i-k)
        {
            pq.pop();
        }
        ans.push_back(pq.top().first); //max element in the current window
    }
    
    return ans;
}

int main()
{
    vector<int> arr = { 2, 3, 7, 9, 5, 1, 6, 4, 3 };
    int k = 3;
    vector<int> result = maxSlidingWindow(arr, k);
    for (auto i : result)
        cout << i << " ";
    return 0;
}

