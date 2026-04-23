#include <iostream>
#include <stdexcept>
#include <type_traits>

struct S {
    S() {
        throw std::runtime_error("");
    }
    ~S() {
        throw std::runtime_error("");
    }
};

int main() {
    std::cout
        << (std::is_nothrow_constructible_v<S> ? 'y' : 'n')
        << (std::is_nothrow_destructible_v<S> ? 'y' : 'n');
}
// Output: ny
// the presence of throw in the constructor and destructor does not influence the exception specifiers.
//If a declaration of a function does not have a noexcept-specifier, the declaration has a potentially throwing exception specification unless it is a destructor or a deallocation function or is defaulted on its first declaration

//We don't provide a noexcept-specifier, and S does not have any subobjects (members or bases) with potentially-throwing destructors. So unlike the constructor, the destructor is non-throwing.
