#include <iostream>

class C {
public:
  C(int i) : i(i) { std::cout << i; }
  ~C() { std::cout << i + 5; }

private:
  int i;
};

int main() {
  const C &c = C(1);
  C(2); //create -> destroyed
  C(3); //create -> destroyed
}
// Output: 127386
//the lifetime of the temporary returned by C(1) is extended for the lifetime of c, to the end of main(). The temporaries returned by C(2) and C(3) are still destroyed at the end of their lines of creation, so they get destroyed before the one returned by C(1).
