#include <iostream>

void print(int x, int y)
{
    std::cout << x << y;
}

int main() {
    int i = 0;
    print(++i, ++i);
    return 0;
}// this is unspecified (but not undefined) behavior, and a conforming implementation can either print 12 or 21, but not for instance 22.
