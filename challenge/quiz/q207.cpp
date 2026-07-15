#include <iostream>
#include <map>

int main() {
    std::map<int, int> m;
    std::cout << m[42];
}
// Output: 0
//The [] operator inserts an element if the key is not present. For a simple int, it inserts 0.


