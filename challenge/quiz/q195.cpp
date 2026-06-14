#include <iostream>
#include <type_traits>

int main() {
  std::cout << std::is_pointer_v<decltype(nullptr)>;
}

// Output: 0
//nullptr is a prvalue of type std::nullptr_t, which is not actually a pointer type. Instead, nullptr is a "null pointer constant" which can be converted to a pointer.


