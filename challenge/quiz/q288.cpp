
#include <iostream>

int main() {
    int I = 1, J = 1, K = 1;
    std::cout << (++I || ++J && ++K);
    std::cout << I << J << K;
}

// Output: 1211

//Unlike |, || guarantees left-to-right evaluation; moreover, the second operand is not evaluated if the first operand evaluates to true.

//So we first evaluate ++I, which is 2. This evaluates to true, so the second operand (++J && ++K) is never evaluated, and J and K do not get incremented.
