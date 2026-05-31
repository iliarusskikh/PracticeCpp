#include <iostream>

int main() {
    int i = 1;
    int const& a = i > 0 ? i : 1;
    i = 2;
    std::cout << i << a;
}
// Output: 21
//So the expression i > 0 ? i : 1; is a prvalue, in other words a temporary. The reference a is bound to that temporary, not to i itself, and i = 2 ends up not modifying a. After i = 2, i is now 2, but a is still 1, and the output of the program is 21.
