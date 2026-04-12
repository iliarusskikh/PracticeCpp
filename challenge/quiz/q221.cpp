
#include <iostream>

struct C {
int& i;
};

int main() {
int x = 1;
int y = 2;

C c{x};
c.i = y;

std::cout << x << y << c.i;
}

// Output: 222
//So c.i = y doesn't modify c to refer to y instead of x, it assigns the value of y to what c.i is referring to. c.i is referring to x, so the value of y is assigned to x.

//When we print the values on the last line, both x and y are 2, and since c.x still refers to x, that also prints 2.

