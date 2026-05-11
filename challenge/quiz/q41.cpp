#include <iostream>
int main() {
  std::cout << 1["ABC"];
}

// Output: B

// 1["ABC"] is identical to *(1+"ABC"). Since the plus operator is commutative, this is identical to *("ABC"+1), which is identical to the more familiar "ABC"[1].


