
#include <algorithm>
#include <iostream>

int main() {
    int x = 10;
    int y = 10;

    const int &max = std::max(x, y);
    const int &min = std::min(x, y);

    x = 11;
    y = 9;

    std::cout << max << min;
}// Output 1111

//So both the evaluation of std::max(x,y) and std::min(x,y) return x, and both references max and min are bound to x.
//
//We then set x to 11, and print max and min, which are now both 11.
