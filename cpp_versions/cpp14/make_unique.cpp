#include <memory>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

std::string append_hello(std::string s){
  // many functions require char; this is a toy example
  // showing use of std::make_unique<char[]> as a safe buffer

  auto c1 = std::make_unique<char[]>(s.size() + 6);
    //[____ ____  ,_,_,_,_,_]

  std::strcpy(c1.get(), s.c_str());
//[G,o,o,d, ,m,o,r,n,i,n,g, ,_,_,_,_,_]
  std::strcat(c1.get(), "hello");
//[G,o,o,d, ,m,o,r,n,i,n,g, ,h,e,l,l,o]
  return std::string(c1.get());
}

int main(){

    std::cout << append_hello("Good morning ") << "\n";

    return EXIT_SUCCESS;
}
