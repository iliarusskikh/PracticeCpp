#include <iostream>
#include <iostream>

bool f() { std::cout << 'f'; return false; }
char g() { std::cout << 'g'; return 'g'; }
char h() { std::cout << 'h'; return 'h'; }

int main() {
    char result = f() ? g() : h();
    std::cout << result;
}
// Output: fhh
//Since f() evaluated to false, h() is selected, h(), and h is printed. g() is never called.

//Finally, on the last line, the value of result, h is printed.
