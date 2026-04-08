#include <iostream>
#include <typeinfo>

void takes_pointer(int* pointer) {
  if (typeid(pointer) == typeid(int[])) std::cout << 'a';
  if (typeid(pointer) == typeid(int*)) std::cout << 'p';
}

void takes_array(int array[]) {
  if (typeid(array) == typeid(int[])) std::cout << 'a';
  if (typeid(array) == typeid(int*)) std::cout << 'p';
}

int main() {
  int* pointer = nullptr;
  int array[1];

  takes_pointer(array);
  takes_array(pointer);

  std::cout << (typeid(int*) == typeid(int[]));
}
// Output: pp0
//array is of type "array of 1 int", which converts to a prvalue (temporary) of type "pointer to int".
//but in void takes_array(int array[]), the type of array is adjusted to "pointer to int".

