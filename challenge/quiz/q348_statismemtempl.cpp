#include <iostream>

struct Printer
{
    Printer() { std::cout << 1; }
};

template <typename T>
struct C
{
    C(T i) { std::cout << i; }
    static inline Printer printer{}; //A static data member of a class template is instantiated only when it is actually used (or when its address is taken, etc.).
};


int main()
{
    C c(2);//The compiler deduces T = int
}

//2
