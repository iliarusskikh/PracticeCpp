#include <iostream>

int main() {
    int a[] = <%1%>; //int a[] = {1};
    std::cout << a<:0:>; //    std::cout << a[0];
}
// Output:1
//a table of alternative tokens is provided, which includes
//- <% and %> for { and }
//- <: and :> for [ and ]
