#include <iostream>

int main() {
  int a = 5, b = 2;
  std::cout << a+++++b;
}
// Compiler error
// So after parsing a++, it is not allowed to just parse +, it has to parse ++. The sequence is thus parsed as:

//a ++ ++ + b
//which is ill-formed since post-increment requires a modifiable lvalue but the first post-increment will produce a prvalue, as per §[expr.post.incr]¶1 in the standard:
//
//The value of a postfix ++ expression is the value of its operand.
//
//(...)
//
//The result is a prvalue.
