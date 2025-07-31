// C++ program to merge k sorted arrays
// of size n each.
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// A pair of pairs, first element is going to
// store value, second element index of array
// and third element index in the array.

typedef pair<int, pair<int,int>> ppi;

// This function takes an array of arrays as an
// argument and all arrays are assumed to be
// sorted. It merges them together and prints
// the final sorted output.
vector<int> mergeKArrays(vector<vector<int> > arr)
{
    vector<int> output;
    //need to store the element, its array and its index;
    //min heap
    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;
    
    //add first element;
    for(int i=0; i<arr.size(); ++i)
    {
        pq.push({arr[i][0],{i,0}});
    }
    
    while(!pq.empty())
    {
        ppi curr = pq.top();
        pq.pop();
        
        int currarr = curr.second.first;
        int curridx = curr.second.second;
        
        output.push_back(curr.first);
        
        if(curridx+1 < arr[currarr].size())
        {
            pq.push({arr[currarr][curridx+1],{currarr, curridx+1}});
        }
    }
    
    return output;
}

// Driver program to test above functions
int main()
{
    // Change n at the top to change number
    // of elements in an array
    vector<vector<int> > arr{ { 2, 6, 12 },
                            { 1, 9 },
                            { 23, 34, 90, 2000 } };

    vector<int> output = mergeKArrays(arr);

    cout << "Merged array is " << endl;
    for (auto x : output)
        cout << x << " ";

    return 0;
}

