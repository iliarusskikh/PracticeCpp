#include <iostream>
#include <map>

int main()
{
  std::map<bool,int> mb = {{1,2},{3,4},{5,0}};
  std::cout << mb.size();
  std::map<int,int> mi = {{1,2},{3,4},{5,0}};
  std::cout << mi.size();
}
// Output: 13
//std::map stores values based on a unique key. The keys for mb are boolean, and 1, 3 and 5 all evaluate to the same key, true.

