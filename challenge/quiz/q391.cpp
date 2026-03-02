#include <iostream>
#include <string>

int main() {
    std::string a = "a";

    auto a1 = [a]() {
        std::string a = "aa";
        return a;
    };

    std::cout << a1();
}
//A variable with the name a is declared twice in this code. Once at the top of main, and then again inside the lambda. In addition, a is captured by the lambda. Which variable is eventually printed inside the lambda? If this at all compiles?

//The lambda ends up returning the local a, with the value "aa", which is eventually printed on the last line of main.


