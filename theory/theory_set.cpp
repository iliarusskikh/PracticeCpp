// C++ program to demonstrate the creation of descending
// order set container
#include <iostream>
#include <set>
#include<unordered_set>
using namespace std;

struct DescendingOrder{
    //overloading comparator
    bool operator()(const int& a, const int& b)const{
        return a>b;
    }
}




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
        //duplicate.erase(it);
}


int main()
{
    //unique values only
    set<int, greater<int> > s1;
    s1.insert(10);
    s1.insert(5);
    s1.insert(12);
    s1.insert(4);

    auto it = s1.find(5);
    //*it

    for (auto& i : s1) {
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
    
    //.size()
    //.empty()
    //.count(10);
    //.lower_bound(10);
    
    
    //using custom comparators
    std::set<int, DescendingOrder> descNumbers;
    descNumbers.insert({5,19,12,11});
    
    //19,12,11,5
    for(const auto& num : descNumbers){
        std::cout << num << " ";
    }
    
    
    
    //for unordered_set
    /*
     bucket_count() - number of buckets in the container
     max_bucket_count()
     bucket_size(n)
     rehash(n)
     ..
     
     
     
     
     */
    
    
    return EXIT_SUCCESS;
}

