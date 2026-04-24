#include <iostream>
#include <utility>

struct A
{
    A() { std::cout << "1"; }
    A(const A&) { std::cout << "2"; }
    A(A&&) { std::cout << "3"; }
};

struct B
{
    A a;
    B() { std::cout << "4"; }
    B(const B& b) : a(b.a) { std::cout << "5"; }
    B(B&& b) : a(b.a) { std::cout << "6"; }
};

int main()
{
    B b1;
    B b2 = std::move(b1);
}

// Output: 1426
//    A() { std::cout << "1"; }
//    B() { std::cout << "4"; }
// b2.a is copy initialized, printing 2.
