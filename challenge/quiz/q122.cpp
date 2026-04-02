#include <iostream>

typedef long long ll;

void foo(unsigned ll) { //treat this as int, ll treated as name
    std::cout << "1";
}

void foo(unsigned long long) {
    std::cout << "2";
}

int main() {
    foo(2ull);
}
// Output: 2

//The parser sees unsigned.
//unsigned by itself means unsigned int (it implies int).
//
//Then it sees ll.
//ll is a type-name (because of typedef long long ll;).
//But because we already had the specifier unsigned (which implies int), the rule says: do not treat ll as continuing the type.
//Instead, treat ll as the parameter name.



//void foo(unsigned long long ll);   // clear and unambiguous
//// or better:
//using ull = unsigned long long;
//void foo(ull x);
