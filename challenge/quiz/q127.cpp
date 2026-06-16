#include <iostream>
#include <type_traits>

int main()
{
  int i, &j = i;
  [=]
  {
    std::cout << std::is_same<decltype    ((j)),     int         >::value
              << std::is_same<decltype   (((j))),    int      &  >::value
              << std::is_same<decltype  ((((j)))),   int const&  >::value
              << std::is_same<decltype (((((j))))),  int      && >::value
              << std::is_same<decltype((((((j)))))), int const&& >::value;
  }();
}
// Output: 00100
//So we're accessing a class member from a const member function, which means that T above is const int, and decltype(E) is const int&. 00100 is printed.

