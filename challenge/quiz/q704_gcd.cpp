#include <iostream>
#include <numeric> // Required for std::gcd

int main() {
    int num1 = 24;
    int num2 = 18;

    // std::gcd automatically handles negative numbers and zero
    int result = std::gcd(num1, num2);

    std::cout << "The GCD of " << num1 << " and " << num2 << " is: " << result << std::endl;

    return 0;
}

/*
 #include <iostream>

 // Recursive function to calculate GCD using the Euclidean algorithm
 int findGCD(int a, int b) {
     if (b == 0) {
         return a;
     }
     return findGCD(b, a % b);
 }

 int main() {
     int num1 = 24;
     int num2 = 18;

     int result = findGCD(num1, num2);

     std::cout << "The GCD of " << num1 << " and " << num2 << " is: " << result << std::endl;

     return 0;
 }

 */
