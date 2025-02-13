//Using Lambdas

#include <functional>
#include <iostream>
using namespace std;

// Function that takes a pointer
// to a function
int invoke(int x, int y, function<int(int, int)> func) {
    return func(x, y);
}
int mylambda(int x, int y, function<int(int,int)>f)
{
    return f(x,y);
}

// Driver Code
int main()
{

    cout<< mylambda(4,2,[](int x,int y)->int{return x*y;});
    // Define lambdas for addition and
    // multiplication operation where
    // we want to pass another function
    // as a parameter

    // Perform Addition
    cout << "Addition: ";
    int k = invoke(20, 10, [](int x,int y) -> int{ return x + y;});

    cout << k << '\n';

    // Perform Multiplication
    cout << "Multiplication:";
    int l = invoke(20, 10,[](int x,int y) -> int{ return x * y; });

    cout << l << '\n';

    return 0;
}
