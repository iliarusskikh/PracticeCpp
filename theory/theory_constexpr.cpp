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
    
    int b =23;
    
    int* a = new int;
    *a = 2;
    a = (int*)&b;
    
    
    const int* c = new int; //or int const*
    //with const int* , c cannot change the content
    //*c = 4; error
    c = (int*)b;
    
    
    int* const d = new int;
    //with const int* , d cannot dereference
    *d = 4;
    //d = (int*)b; //error
  
    
    const int* const e = new int;
    //with const int* , e cannot dereference
    //*e = 4;//cannot chagne the value
    //e = (int*)b; //error
    
    
    const int* p1 = &value; //cant modify *p1
    int* const p2 = &value; //cant modify p2
    const int* const p3 = &value; //cant modify p3 or *p3
    
    
    
    
    
    
    return 0;
}

