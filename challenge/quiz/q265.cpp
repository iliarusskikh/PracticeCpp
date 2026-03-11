#include <iostream>

void f(char*&&) { std::cout << 1; } //rvalue reference to char* - this is being called

void f(char*&) { std::cout << 2; } //lvalue reference to char*
//Meaning it requires a named pointer variable.


int main() {
    char c = 'a';
    f(&c);
}
// c is lvalue of type char
// &c → prvalue of type char*
//&c is NOT an lvalue

//we could have chagned to char* p = &c; - lvalue

//1
