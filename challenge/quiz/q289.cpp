According to the C++23 standard, what is the output of this program?

    
#include <iostream>

void f(int a = []() { static int b = 1; return b++; }())
{
    std::cout << a;
}

int main()
{
    f();
    f();
}
// Output 1 2


//The static variable b is post-incremented, which means it increments by one, but returns the previous value. So for the first call to f(), b is initialized to 1, then b++ increments it to 2, while still returning 1. The 1 is assigned to a, and 1 is printed.

//For the second call, the lambda is called again, returning a post-incremented b. The question is then if this is the same b as in the first call (so 2 is returned), or if it's a different b (so 1 is returned again).


