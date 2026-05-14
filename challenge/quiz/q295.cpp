#include <iostream>

char a[2] = "0";

struct a_string {
    a_string() { *a='1'; }
    ~a_string() { *a='0'; }
    const char* c_str() const { return a; }
};

void print(const char* s) { std::cout << s; }
a_string make_string() { return a_string{}; }

int main() {
    a_string s1 = make_string();
    print(s1.c_str());

    const char* s2 = make_string().c_str();
    print(s2);

    print(make_string().c_str());
}
// Output: 101

/*
 a_string s1 = make_string(); creates an a_string, and a is set to 1. This object is not destroyed (and a set back to 0 again) until at the very end of main(), after we're done printing.

 Then print(s1.c_str()); is called, printing the value of a, which is now 1.

 Next, we do const char* s2 = make_string().c_str();. The temporary a_string created by the call to make_string sets a to 1, but then back to 0 again when it is destroyed. By the time we get to print(s2);, it prints 0.
 */
