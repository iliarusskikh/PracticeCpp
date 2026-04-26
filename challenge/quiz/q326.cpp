#include <iostream>

struct S;

S foo(S s); // S has only been forward declared at this point

struct S{};

S foo(S s) { return {}; }

int main(){
    const S s = foo(S{});
    std::cout << "ok";
}

// Output: ok

//When a function is called, the type of any parameter shall not be a class type that is either incomplete or abstract.

//There is however no such requirement for function declarations.
