#include <iostream>

void check(int and x) { std::cout << "a"; }

void check(int bitand x) { std::cout << "b"; }

int main()
{
    check(3);
}
//output: a
//the tokens and and bitand behaves exactly like && and &, respectively, except for their spelling.
//Therefore, int and x declares x as a rvalue reference to int and int bitand x declares x as a lvalue reference to int. It is as if the check functions had the signatures int && x and int & x, respectively.
