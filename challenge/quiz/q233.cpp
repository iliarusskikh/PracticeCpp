#include <type_traits>
#include <iostream>

struct X {
    int f() const&&{
        return 0;
    }
};

int main() {
    auto ptr = &X::f;
    std::cout << std::is_same_v<decltype(ptr), int()>
              << std::is_same_v<decltype(ptr), int(X::*)()>;
}
// Output: 00
//the ref-qualifier (in this case const&&) is part of the type and thus the type of ptr is int(X::*)() const&&.
