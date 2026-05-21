#include <iostream>

struct X {
    int var1 : 3;
    int var2;
};

int main() {
    X x;
    std::cout << (&x.var1 < &x.var2);
}
// Output: compiler error - int var1 : 3; declares a bit-field, and you can not apply operator& to a bit-field.
