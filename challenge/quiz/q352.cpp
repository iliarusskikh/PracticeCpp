#include <iostream>
#include <typeinfo>
#include <vector>

typedef std::vector<int> TVint;

int main() {
    TVint t(1);
    std::cout << (typeid(t) == typeid(std::vector<int>));
}

// Output: 1
//The typedef specifier provides a way for declaring a type alias. However, it does not introduce a new type-id.
