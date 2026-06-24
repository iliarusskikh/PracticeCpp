#include <iostream>
#include <memory>

struct S {
    S(int i) : i_(i){}
    S* operator&() const;
    int i_;
};

S global{1};
S* S::operator&() const { return &global; }

int main() {
    S s(2);
    S* ptr = std::addressof(s);
    std::cout << ptr->i_;
}

// Output:2
//So addressof ignores the overloaded operator&, and this is indeed its purpose. It computes the actual address of s, and we can then print its member i_ which holds the value 2.


