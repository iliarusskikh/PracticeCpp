//Insert and Merge Interval

//Given a set of non-overlapping intervals[][] where intervals[i] = [starti , endi] represent the start and the end of the ith event and intervals is sorted in ascending order by starti and a new interval, insert the interval at the correct position such that after insertion, the intervals remain sorted. If the insertion results in overlapping intervals, then merge the overlapping intervals. Assume that the set of non-overlapping intervals is sorted based on start time.
//
//Examples:
//
//Input: intervals[][] = [[1, 3], [4, 5], [6, 7], [8, 10]], newInterval[] = [5, 6]
//Output: [[1, 3], [4, 7], [8, 10]]
//Explanation: The intervals [4, 5] and [6, 7] are overlapping with [5, 6]. So, they are merged into one interval [4, 7].
//
//Input: intervals[][] = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], newInterval[]  = [4, 9]
//Output: [[1, 2], [3, 10], [12, 16]]
//Explanation: The intervals [ [3, 5], [6, 7], [8, 10] ] are overlapping with [4, 9]. So, they are merged into one interval [3, 10].


//[Expected Approach] Contiguous Interval Merging - O(n) Time and O(n) Space
//When we add a new interval, it may overlap with some contiguous intervals in the array. The overlapping intervals can be found in a contiguous subarray because the intervals array is already sorted. To remove overlapping we find these overlapping interval's subarray and merge them with new interval, to form a single merged interval.
//
//Now to maintain the order sorted, we first add the lower intervals, then this merged interval, and finally the remaining intervals in the result.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to insert and merge intervals
vector<vector<int>> insertInterval(vector<vector<int>>& intervals, vector<int> &newInterval) {
    vector<vector<int>> res;
    int i = 0;
    int n = intervals.size();

    // Add all intervals that come before the new interval
    while (i < n && intervals[i][1] < newInterval[0]) {
        res.push_back(intervals[i]);
        i++;
    }

    // Merge all overlapping intervals with the new interval
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval);

    // Add all the remaining intervals
    while (i < n) {
        res.push_back(intervals[i]);
        i++;
    }

    return res;
}

int main() {
    vector<vector<int>> intervals = {{1, 3}, {4, 5}, {6, 7}, {8, 10}};
    vector<int> newInterval = {5, 6};
    
    vector<vector<int>> res = insertInterval(intervals, newInterval);
      
    for (vector<int> interval: res) {
          cout << interval[0] << " " << interval[1] << "\n";
    }
    return 0;
}
