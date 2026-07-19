#include <iostream>

struct A {};
struct B {};

template<typename T = A>
struct X;

template<>
struct X<A> {
    static void f() { std::cout << 1; }
};

template<>
struct X<B> {
    static void f() { std::cout << 2; }
};

template<template<typename T = B> class C>
void g() {
    C<>::f();
}

int main() {
    g<X>();
}
// Output:2
//when g<X>() is called, it is equivalent to calling g<X<B>>(), which in turn calls X<B>::f(). As X<B>::f() is specialized to print 2, the output of the program is 2.

