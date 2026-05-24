#include <iostream>

int main() {
    int n = sizeof(0)["abcdefghij"];
    std::cout << n;
}
// Output:1
//0th element of "abcdefghij", which is a, which is a char. And the result of sizeof('a') will be 1

