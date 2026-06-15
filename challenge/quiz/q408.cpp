#include <iostream>

int main() {
    std::cout << (4.0f < 5.0) ? "yes" : "no";
}
// Output: 1

//So first, we evaluate std::cout << (4.0f < 5.0), which prints 1 since 4.0f is less than 5.0f.
//
//true ? "yes" : "no", which returns "yes". That value is simply discarded (since it's not used for anything) and the program ends.
//
//To fix this program, and give it the intended meaning, we need to add an extra set of parentheses, like this:
//
//std::cout << ((4.0f < 5.0) ? "yes" : "no");
