#include <vector>
#include <iostream>

int main() {
  std::vector<char> delimiters = { ",", ";" };
  std::cout << delimiters[0];
}

// Output: program is undefined
//Here we are trying to initialize a vector<char> using two string literals, not two chars.
