#include <iostream>

template <class T> void f(T &i) { std::cout << 1; } //define a template

template <> void f(const int &i) { std::cout << 2; } //define an explicit specialization (wont compile alone)

int main() {
  int i = 42;
  f(i);
    
  return 0;
}

// output:1
//The types to which the references refer are int for S1 and const int for S2. Those are indeed the same types except for top-level cv-qualifiers, and const int is indeed more cv-qualified than int, so S1 is a better conversion sequence and the primary function template is the best viable function.

//The primary function template is thus called, and 1 is printed.
