#include <iostream>

class A {
public:
  
      // Static variable with static scope i.e. accessible
      // in whole class
    static int staticVar;
};

int A::staticVar = 1;

int main() {
  
      // Access static variable
      std::cout << A::staticVar;

    return 0;
}
