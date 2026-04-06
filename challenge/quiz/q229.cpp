#include <iostream>

int a = 1;

int main() {
    auto f = [](int b) { return a + b; };

    std::cout << f(4);
}// Output: 5

//Only local variables may be captured by a lambda. a is a global variable with static storage duration and may not be captured.
