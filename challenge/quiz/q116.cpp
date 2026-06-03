
#include <iostream>
#include <utility>

int y(int &) { return 1; }
int y(int &&) { return 2; }

template <class T> int f(T &&x) { return y(x); }
template <class T> int g(T &&x) { return y(std::move(x)); }
template <class T> int h(T &&x) { return y(std::forward<T>(x)); }

int main() {
int i = 10;
std::cout << f(i) << f(20); //11
std::cout << g(i) << g(20);//22
std::cout << h(i) << h(20);//12
return 0;
}
// Output: 112212

//For the first example, y(int&) is called for both cases. Output: 11.
//For the second example, std::move(x) obtains an rvalue reference, and y(int&&)is called for both cases. Output: 22.
//For the third example, std::forward<T>(x) obtains an lvalue reference when x is an lvalue reference, and an rvalue reference when x is an rvalue reference, resulting in first calling y(int&) and then calling y(int&&). Output: 12.
