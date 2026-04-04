#include <iostream>
#include <sstream>

int main() {
  std::stringstream ss("a");
  std::cout << ss.str();
  ss << "b";
  std::cout << ss.str();
}
// Output: ab

/*
 stringstream is backed by a character buffer. Initializing it with a string initializes the buffer with that string, in this case a. Calling str() returns the contents of the buffer, and we print a.

 operator<< writes to the next position in the buffer, in this case the beginning of the buffer, overwriting whatever is already there. A b is written, overwriting the a which was previously in the buffer.

 Finally, str() is called again, this time printing b.

 We can change this behaviour by initializing stringstream like this:

 std::stringstream ss("a", std::ios_base::out | std::ios_base::ate);
 Then the a doesn't get overwritten, and the program instead outputs aab, where a comes from the first call to str(), and ab comes from the second call to str().
 */
