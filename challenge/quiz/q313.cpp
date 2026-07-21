#include <iostream>
#include <utility> // Required for std::forward


void f(float &&) { std::cout << "f"; } //overload for rvalues
void f(int &&) { std::cout << "i"; }//overload for rvalues

template <typename... T>
void g(T &&... v) //named variables turn to lvalues
{
    (f(v), ...);//When v is expanded in (f(v), ...), the individual arguments passed to f are treated as lvalues.
    
    //to preserve the rvalue:
    // std::forward restores the original rvalue status
//    (f(std::forward<T>(v)), ...);
}

int main()
{
    g(1.0f, 2); //rvalues passed
}
// Output: if

/*
 You pass 1.0f (an rvalue float) to g.
 The template deduces T as float, and the parameter v becomes a named variable of type float&&.
 When f(v) is called, v is evaluated as an lvalue float.
 
 Now, look at your available f overloads:void f(float &&) — Requires an rvalue.
 It cannot accept an lvalue float.void f(int &&) — Requires an rvalue.
 It cannot accept an lvalue float.
 Because there is no exact match for an lvalue float, C++ looks for standard implicit conversions.
 An lvalue float can be converted to an rvalue int via a standard floating-to-integral conversion.
 */
