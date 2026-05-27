#include <iostream>

template<class T>
void f(T) { std::cout << 1; }

template<>
void f<>(int*) { std::cout << 2; }

template<class T>
void f(T*) { std::cout << 3; }

int main() {
    int *p = nullptr;
    f( p );
}

// Output: 3
//The name f is overloaded by the two function templates void f(T) and void f(T*). Note that overload resolution only considers the function templates, not the explicit specialization void f<>(int*)! For overload resolution, first we deduce the template arguments for each function template, and get T = int * for the first one, and T = int for the second.
