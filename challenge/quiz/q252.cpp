#include <iostream>

int main() {
    int i = '3' - '2';
    std::cout << i;
}

//So we know that the difference between '3' and '2' is 1, even if we don't know their actual values. Importantly, this is only true for decimal digits, and not for instance for regular letters. There is no guarantee that 'b' - 'a' is 1.
