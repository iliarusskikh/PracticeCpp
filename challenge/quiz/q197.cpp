#include <iostream>

int j = 1;

int main() {
  int& i = j, j;
  j = 2;
  std::cout << i << j;
}
//12
//The line int& i = j, j; declares two variables i and j.
//However, the program point where we set j = 2 does follow the locus of the local j, so we modify the local j, and the j that i refers to is not affected.


