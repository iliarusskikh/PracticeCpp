//Convert Array into Zig-Zag fashion

//arr[0] < arr[1]  > arr[2] < arr[3] > arr[4] < ...
//
//Input: N = 7, arr[] = [4, 3, 7, 8, 6, 2, 1]
//Output: [3, 7, 4, 8, 2, 6, 1]
//Explanation:  The given array is in zig-zag pattern as we can see 3 < 7 > 4 < 8 > 2 < 6 >1




//[Expected Approach] Rearranging Triplets using Flag - O(N) time and O(1) Space

//The idea is that for each triplet, the middle element should be greater than its adjacent neighbours. So, for each triplet:
//
//First check the left neighbour with the middle element. If middle is smaller, swap the elements.
//Then check the middle with right neighbour. If middle is smaller, swap the elements.
//Repeat the process till complete array is traversed.

// C++ program to sort an array in Zig-Zag form
#include <iostream>
using namespace std;

// Program for zig-zag conversion of array
void zigZag(int arr[], int n)
{
    // Flag true indicates relation "<" is expected,
    // else ">" is expected. The first expected relation
    // is "<"
    bool flag = true;

    for (int i = 0; i <= n - 2; i++) {
        if (flag) /* "<" relation expected */
        {
            /* If we have a situation like A > B > C,
            we get A > C < B by swapping B and C */
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
        else /* ">" relation expected */
        {
            /* If we have a situation like A < B < C,
            we get A < C > B by swapping B and C */
            if (arr[i] < arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
        flag = !flag; /* flip flag */
    }
}

// Driver program
int main()
{
    int arr[] = { 4, 3, 7, 8, 6, 2, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    zigZag(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}

// This code is contributed by Sania Kumari Gupta
// (kriSania804)
