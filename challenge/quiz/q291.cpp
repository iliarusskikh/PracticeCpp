#include <iostream>

int _global = 1;

int main() {
  std::cout << _global;
}

// Output: undefined

//The standard defines some identifiers as reserved to the implementation.


//In addition, some identifiers appearing as a token or preprocessing-token are reserved for use by C++ implementations and shall not be used otherwise; no diagnostic is required.

