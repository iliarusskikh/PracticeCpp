//functors
// A C++ program uses transform() in STL to add
// 1 to all elements of arr[]
#include <iostream>
using namespace std;

int increment(int x) { return (x+1); }

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    // Apply increment to all elements of
    // arr[] and store the modified elements
    // back in arr[]
    transform(arr, arr+n, arr, increment);//if increment was a class, then increment(value), called as contructor
    //from arr address to arr+n address, then store it into arr!
    for (int i=0; i<n; i++)
        cout << arr[i] <<" ";

    return 0;
}

