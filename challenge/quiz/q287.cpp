#include <string>
#include <iostream>

int main() {
  using namespace std::string_literals;
  std::string s1("hello world",5); //"hello world" is a raw C-style string literal (const char*).
    //Passing it alongside 5 invokes the std::string(const char* s, size_t count) constructor.
    //This takes the first 5 characters of the string.
    
  std::string s2("hello world"s,5);//"hello world"s uses the s suffix from std::string_literals, turning it into a temporary std::string object.
    //Passing it alongside 5 invokes the substring constructor: std::string(const std::string& str, size_t pos, size_t count = npos).
    
    //This treats the number 5 as the starting index (position) rather than a count.

  std::cout << s1 << s2;
}

// Output:Hello World
