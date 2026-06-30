#include <iostream>
#include <type_traits>

template<typename T, typename U>
void f(T, U) {
    std::cout << std::is_same_v<T, U>;
}

int main() {
    int i = 0;
    double d = 0.0;
    f(i, d);
    f<int>(i, d);
    f<double>(i, d);
}
// Output: 001

//In the case of f<double>(i, d), we specify the type of T as double. The type of U is deduced as before to double. The types are the same, and 1 is printed.


