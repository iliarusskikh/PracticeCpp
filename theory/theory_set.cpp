// C++ program to demonstrate the creation of descending
// order set container
#include <iostream>
#include <set>
#include<unordered_set>
using namespace std;


void printDuplicates(int arr[], int n)
{
    // declaring unordered sets for checking and storing
    // duplicates
    unordered_set<int> intSet;
    unordered_set<int> duplicate;

    // looping through array elements
    for (int i = 0; i < n; i++) {
        // if element is not there then insert that
        if (intSet.find(arr[i]) == intSet.end())
            intSet.insert(arr[i]);

        // if element is already there then insert into
        // duplicate set
        else
            duplicate.insert(arr[i]);
    }

    // printing the result
    cout << "Duplicate item are : ";
    unordered_set<int>::iterator itr;

    // iterator itr loops from begin() till end()
    for (itr = duplicate.begin(); itr != duplicate.end();
         itr++)
        cout << *itr << " ";
}


int main()
{
    //unique values only
    set<int, greater<int> > s1;
    s1.insert(10);
    s1.insert(5);
    s1.insert(12);
    s1.insert(4);

    for (auto i : s1) {
        cout << i << ' '; //12,10,5,4.. discending
    }
    
    
    s1.erase(s1.begin(), s1.find(30));//erase all elements until 30 found

    // remove element with value 50 in s2
    s1.erase(50);
    
    int arr[] = { 1, 5, 2, 1, 4, 3, 1, 7, 2, 8, 9, 5 };
    int n = sizeof(arr) / sizeof(int);

    printDuplicates(arr, n);
    if (s1.find(10) != s1.end()) {
        cout << "element found." << endl;
    }
    
    
    multiset<int> q;
    q.insert(10);
    q.insert(10);
    q.insert(10);
    // it will remove only one value of
    // 10 from multiset
    q.erase(q.find(10));

    // it will give output 2
    cout << q.count(10) << endl;
    
    return 0;
}

