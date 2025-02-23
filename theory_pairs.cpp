// CPP program to illustrate Pair in STL
#include <iostream>
#include <utility>
using namespace std;

// Driver Code
int main()
{
    // defining a pair
    pair<int, char> PAIR1;
    pair<string, double> PAIR2("Hello", 1.23);
    pair<int, char> PAIR3;
    PAIR3 = make_pair(4,'b');
    PAIR3 = {4,'v'};
    
    // first part of the pair
    PAIR1.first = 100;
    // second part of the pair
    PAIR1.second = 'G';

    cout << PAIR1.first << " ";
    cout << PAIR1.second << endl;
    
    
    pair<int, pair<int, int> > pair3 = { 3, { 4, 7 } };

    int a;
    int b = 0;
    pair<int, int> pair2 = { 3, 4 };
    tie(a, ignore) = pair2; //unpacking pairs
    tie(a, b) = pair3.second;
    // prints old value of b
    cout << a << " " << b << "\n";

    return 0;
}

