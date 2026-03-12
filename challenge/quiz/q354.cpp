#include <cstdlib>
#include <iostream>

struct S {
    char s;
    S(char s): s{s} {}
    ~S() { std::cout << s; }
};

S a('a');

int main() {
    S b('b');
    std::exit(0);
}
// a
//The std::exit function calls the destructors of all objects with static storage duration, but is not responsible for destroying local variables.
//Therefore, when std::exit(0); is called, only the destructor of a is called; b is a local variable and its destructor is thus not called.
