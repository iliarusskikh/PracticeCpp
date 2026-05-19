#include <iostream>

int main() {
    const int i = 0;
    int& r = const_cast<int&>(i);
    r = 1;
    std::cout << r;
}

// Output: Modifying a const object results in undefined behavior. Casting away constness does not help.


