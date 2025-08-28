//Given an array arr[], where arr[i] represents the number of pages in the i-th book, and an integer k denoting the total number of students, allocate all books to the students such that:
//
//Each student gets at least one book.
//Books are allocated in a contiguous sequence.
//The maximum number of pages assigned to any student is minimized.

//Input: arr[] = [12, 34, 67, 90], k = 2
//Output: 113
//Explanation: Books can be distributed in following ways:
//
//[12] and [34, 67, 90] - The maximum pages assigned to a student is  34 + 67 + 90 = 191.
//[12, 34] and [67, 90] - The maximum pages assigned to a student is 67 + 90 = 157.
//[12, 34, 67] and [90] - The maximum pages assigned to a student is 12 + 34 + 67 = 113.


//[Naive Approach] By Iterating Over All Possible Page Limits
/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// function to check if books can be allocated to
// all k students without exceeding 'pageLimit'
bool check(vector<int> &arr, int k, int pageLimit) {
    
    // starting from the first student
    int cnt = 1;
    int pageSum = 0;
    for(int i = 0; i < arr.size(); i++) {
        
        // if adding the current book exceeds the page
        // limit, assign the book to the next student
        if(pageSum + arr[i] > pageLimit) {
            cnt++;
            pageSum = arr[i];
        }
        else {
            pageSum += arr[i];
        }
    }
    
      // if books can assigned to less than k students then
    // it can be assigned to exactly k students as well
    return (cnt <= k);
}

int findPages(vector<int> &arr, int k) {
    
    // if number of students are more than total books
    // then allocation is not possible
    if(k > arr.size())
        return -1;
        
    // minimum and maximum possible page limits
    int minPageLimit = *max_element(arr.begin(), arr.end());
    int maxPageLimit = accumulate(arr.begin(), arr.end(), 0);
    
    // iterating over all possible page limits
    for(int i = minPageLimit; i <= maxPageLimit; i++) {
        
        // return the first page limit with we can
        // allocate books to all k students
        if(check(arr, k, i))
            return i;
    }
    
    return -1;
}

int main() {
    vector<int> arr = {12, 34, 67, 90};
    int k = 2;
    cout << findPages(arr, k);
    return 0;
}
*/



//[Expected Approach] Using Binary Search
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// function to check if books can be allocated to
// all k students without exceeding 'pageLimit'
bool check(vector<int> &arr, int k, int pageLimit) {
    
    // starting from the first student
    int cnt = 1;
    int pageSum = 0;
    for(int i = 0; i < arr.size(); i++) {
        
        // if adding the current book exceeds the page
        // limit, assign the book to the next student
        if(pageSum + arr[i] > pageLimit) {
            cnt++;
            pageSum = arr[i];
        }
        else {
            pageSum += arr[i];
        }
    }
    
    // if books can assigned to less than k students then
    // it can be assigned to exactly k students as well
    return (cnt <= k);
}

int findPages(vector<int> &arr, int k) {
    
    // if number of students are more than total books
    // then allocation is not possible
    if(k > arr.size())
        return -1;
        
    // search space for Binary Search
    int lo = *max_element(arr.begin(), arr.end());
    int hi = accumulate(arr.begin(), arr.end(), 0);
    int res = -1;
    
    while(lo <= hi) {
        int mid = lo + (hi - lo)/2;
        
        if(check(arr, k, mid)){
            res = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    
    return res;
}

int main() {
    vector<int> arr = {12, 34, 67, 90};
    int k = 2;
    cout << findPages(arr, k);
    return 0;
}


