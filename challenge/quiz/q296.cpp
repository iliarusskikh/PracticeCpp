#include <iostream>

struct S {
    int one;
    int two;
    int three;
};

int main() {
    S s{1,2};
    std::cout << s.one;
}
// Output: 1
//You are actually allowed to specify fewer initializers than a struct/class has members, as long as that struct/class is an aggregate.

// if the element is not a reference, the element is copy-initialized from an empty initializer list

