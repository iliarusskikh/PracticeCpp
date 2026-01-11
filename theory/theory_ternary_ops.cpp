#include <iostream>

int main() {
    int a = 5;
    int b = 10;

    // Ternary operator to find the maximum of two numbers
    int max = (a > b) ? a : b;

    std::cout << "The maximum of " << a << " and " << b << " is: " << max << std::endl;

    // Another example: Check if even or odd
    std::string parity = (a % 2 == 0) ? "even" : "odd";
    std::cout << a << " is " << parity << std::endl;

    // Nested ternary: Classify number
    std::string classification = (a > 0) ? "positive" : ((a < 0) ? "negative" : "zero");
    std::cout << a << " is " << classification << std::endl;

    return 0;
}
