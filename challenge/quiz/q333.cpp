#include <iostream>

int main()
{
    int x = 3;
    while (x --> 0) // x goes to 0
    {
        std::cout << x;
    }
}
// Output: 210
//x is 2 on the first iteration, 1 on the next, and 0 on the last (since we're post decrementing it and comparing the not-yet-decremented value to 0).
