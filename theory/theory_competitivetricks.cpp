/* ------------------ */
//Checking if the number is even or odd without using the % operator
if (num & 1)
   cout << "ODD";
else
   cout << "EVEN";

/* ------------------ */
//Fast Multiplication or Division by 2
// Multiply n with 2
n = n << 1;
// Divide n by 2
n = n >> 1;

/* ------------------ */
//Swapping of 2 numbers using XOR
// A quick way to swap a and b
a ^= b;
b ^= a;
a ^= b;

/* ------------------ */
//Avoiding the use of strlen():
// Use of strlen() can be avoided by:
for (i=0; s[i]; i++)
{
}
// loop breaks when the character array ends.

/* ------------------ */
//calculating the most significant digit
Suppose the number is N then
Let int K = log10(N); // number of digits in a number=log10(N)+1
And int X = pow(10, K);
Then int ans=N/X will be the most significant digit

using namespace std;

int MSD(int n){
    if(n == 0)
        return 0;
    int k = log10(n);
    int x = pow(10,k);
    int ans = n/x;
    return ans;
}

int main() {
    int n;
    cin >> n;
    cout << MSD(n) << endl;
    return 0;
}

/* ------------------ */
//if number is of power of 2
/* Function to check if x is power of 2*/
bool isPowerOfTwo (int x)
{
/* First x in the below expression is
    for the case when x is 0 */
return x && (!(x&(x-1)));
}

/* ------------------ */
//Copy Algorithm: used to copy elements from one container to another.
int source[5] = {0, 12, 34, 50, 80};
int target[5];
// copy 5 elements from source to target
copy_n(source, 5, target);

/* ------------------ */
//The Iota Algorithm The algorithm iota() creates a range of sequentially increasing values, as if by assigning an initial value to *first, then incrementing that value using prefix ++. In the following listing, iota() assigns the consecutive values {10, 11, 12, 13, 14} to the array arr, and {‘a’, ‘b’, ‘c’} to the char array c[].

int a[5] = {0};
char c[3] = {0};

// changes a to {10, 11, 12, 13, 14}
iota(a, a+5, 10);
iota(c, c+3, 'a'); // {'a', 'b', 'c'}


/* ------------------ */


