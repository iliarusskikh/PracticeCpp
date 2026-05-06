#include<iostream>

int foo()
{
  return 10;
}

struct foobar
{
  static int x;
  static int foo()
  {
    return 11;
  }
};

int foobar::x = foo();

int main()
{
    std::cout << foobar::x;
}

// Output: 11
//In the statement int foobar::x = foo();
// we redeclare the variable x. Its target scope is a class scope introduced by the declaration of the class foobar. The portion after x is also included in that scope. So when looking for foo we find foobar::foo there and don't search any further.*/
