#include <iostream>

int main() {
    int n = 3;
    int i = 0;

    switch (n % 2) {
    case 0:
        do {
        ++i;
    case 1: //both cases visited
        ++i;
        } while (--n > 0);
    }

    std::cout << i;
}
// Output: 5
//
