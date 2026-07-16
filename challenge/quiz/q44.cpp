#include <iostream>
struct X {
  virtual void f() const { std::cout << "X"; }
};

struct Y : public X {
  void f() const { std::cout << "Y"; }
};

void print(const X &x) { x.f(); }

int main() {
  X arr[1];
  Y y1;
  arr[0] = y1;
  print(y1);
  print(arr[0]);
}

// Output: YX
//arr is an array of X, not of pointers to X. When an object of type Y is stored in it, it is converted to X, and we lose the "Y part" of the object. This is commonly known as "slicing".


