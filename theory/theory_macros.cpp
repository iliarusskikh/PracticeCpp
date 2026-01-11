#include <iostream>

// Much safer version
#define SQUARE_SAFE(x)   ((x) * (x))
#define MAX_SAFE(a,b)    (((a) > (b)) ? (a) : (b))

int main()
{
    int a = 5;
    std::cout << "SQUARE_SAFE(a+2) = " << SQUARE_SAFE(a+2) << "\n";  // correct: 49

    int x = 10;
    std::cout << "MAX_SAFE(x++, 20) = " << MAX_SAFE(x++, 20) << "\n";
    // Still dangerous - x++ may be evaluated twice depending on which side wins

    return 0;
}

/*
 //avoid macros
 
 #include <iostream>
 #include <algorithm>  // for std::max

 // 1. constexpr function (C++11+) - best for constants & simple calculations
 constexpr double square(double x) {
     return x * x;
 }

 constexpr int max_int(int a, int b) {
     return a > b ? a : b;
 }

 // 2. Even better - inline function or template
 template<typename T>
 constexpr T square_t(T x) {
     return x * x;
 }

 int main()
 {
     constexpr double s1 = square(5.5);           // computed at compile time
     constexpr int m1 = max_int(10, 25);

     std::cout << "square(5.5) = " << s1 << "\n";
     std::cout << "square_t(8) = " << square_t(8) << "\n";

     // Safe, no double evaluation
     int x = 10;
     std::cout << "std::max(x++, 20) = " << std::max(x++, 20) << "\n";
     std::cout << "x after = " << x << "\n";      // x increased only once

     return 0;
 }
 */
