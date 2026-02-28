#include <vector>
#include <iostream>

std::vector<int> v;

int f1() {
  v.push_back(1);
  return 0;
}

int f2() {
  v.push_back(2);
  return 0;
}

void g(int, int) {}

void h() {
  g(f1(), f2());
}

int main() {
  h();
  h();
  std::cout << (v[0] == v[2]);
}

/*
 
 The evaluation order of function argument expressions is unspecified, all we know is that they will all happen before ("be sequenced before") the contents of the called function.

 In particular, in the expression g(f1(), f2()), we don't know whether f1 or f2 will be sequenced first, we only know that they will both be sequenced before the body of g.

 Also: There isn't even a requirement on the implementation that f1 and f2 gets evaluated in the same order each time. So after calling h twice, v can contain 1212, 2121, 1221 or 2112.
 
 */
