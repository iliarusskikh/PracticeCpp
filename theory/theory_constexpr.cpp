/*The constexpr keyword is similar to const keyword and is also used to declare constants in C++. But the major difference is that the constexpr constants are initialized at compiler time, which is why their value must be known at the compile time. On the other hand, const keyword constants can be initialized at runtime and compile time.

 constexpr guarantees optimisation at compile time
*/

#include <iostream>

struct Point {
    int x, y;
    constexpr Point(int x, int y) : x(x), y(y) {}
    constexpr int distance() const { return x * x + y * y; }
};

int main() {
  
    // Defining constant
    int constexpr hoursIn_day = 24;

    // Printing value
    std::cout << hoursIn_day;

    constexpr Point p(3, 4);
    constexpr int dist = p.distance(); // 25, computed at compile-time
    
    
    return 0;
}

