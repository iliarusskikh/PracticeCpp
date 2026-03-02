#include <iostream>

struct S {
    template <typename Callable>
    void operator[](Callable f) {
        f();
    }
};

int main() {
    auto caller = S{};
    caller[ []{ std::cout << "C";} ];
}
// Compiler error - Two consecutive square brackets are normally used for [[attributes]], and indeed we are not allowed to use them like this here.
//
