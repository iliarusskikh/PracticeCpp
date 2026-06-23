#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same_v<
        void(int),
        void(const int)>;

    std::cout << std::is_same_v<
        void(int*),
        void(const int*)>;
}

// Output: 10
//The constness of parameters are not part of the function type.

//So in the first case, the type of void(const int) is actually void(int). The types are the same, and 1 is printed.

//The pointers themselves are not const, so there's no const to remove. The types of the functions are different, and 0 is printed.
