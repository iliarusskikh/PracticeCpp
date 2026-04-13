#include <iostream>

struct S
{
  S() = delete;
  int x;
};

int main()
{
  auto s = S{};
  std::cout << s.x;
}
// Output: Compile error
//Here, the S default constructor is considered user-declared, so S isn't an aggregate, and S{} is using value initialization, and the program is ill-formed.


