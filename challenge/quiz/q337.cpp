#include <iostream>
#include <type_traits>

int main() {
    auto a = "Hello, World!";
    std::cout << std::is_same_v<decltype("Hello, World!"), decltype(a)>;

    return 0;
}
//Output: 0
//A string literal is an lvalue, and its type is "array of n const char", so decltype("Hello, World!") is const char(&)[14].

//the type of a is the result of array-to-pointer conversion of the type of "Hello, World!" (const char(&)[14]) which is const char*.

