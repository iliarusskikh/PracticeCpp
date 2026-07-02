#include <iostream>

template <typename T>
struct A {
    static_assert(T::value);
};

struct B {
    static constexpr bool value = false;
};

int main() {
    A<B>* a;
    std::cout << 1;
}
// Output:1

//We're declaring a pointer to an A<B>. In the definition of A, we do static_assert(T::value), where T::value becomes B::value, which is false.

//The class template specialization A<B> has not been explicitly instantiated nor explicitly specialized, so the question is then whether it's implicitly instantiated. We're only declaring a pointer to it, which doesn't require a completely-defined object type, so it's not instantiated. The program compiles just fine, and 1 is printed.

//If we had for instance done A<B> a instead, we would have instantiated A<B>, and gotten a compilation error.
