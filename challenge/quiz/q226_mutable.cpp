#include <iostream>
#include <utility>

struct X {
    X() { std::cout << "1"; }
    X(X &) { std::cout << "2"; }
    X(const X &) { std::cout << "3"; }
    X(X &&) { std::cout << "4"; }
    ~X() { std::cout << "5"; }
};

struct Y {
    mutable X x;
    Y() = default;
    Y(const Y &) = default; //since defined, the compiler does not generate a move constructor at all.
    //if we remove it, The compiler would implicitly declare both a copy constructor and a move constructor for Y.
};

int main() {
    Y y1;
    Y y2 = std::move(y1);
}
// Output 1255

//since Y has no move constructor, its copy constructor is called.

//The mutable specifier on a class data member nullifies a const specifier applied to the containing class object and permits modification of the mutable class member even though the rest of the object is const

//So x is considered non-const, and X(X &) is a better match to overload resolution than X(const X &), because in the latter case, a const conversion has to happen. So X(X &) is called, printing 2.
