#include <iostream>

void print(char const *str) { std::cout << str; }
void print(short num) { std::cout << num; }

int main() {
  print("abc");
  print(0);
  print('A');
}


//Output: Compilation error

// Because 0 is a null pointer constant, it can be converted implicitly into any pointer type with a single conversion.

//(b) Because 0 is of type int, it can be converted implicitly to a short with a single conversion too.

//In our case, both are standard conversion sequences with the same conversion rank. Since no function is better than the other, the call is ill-formed.
