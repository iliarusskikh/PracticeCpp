#include <iostream>
#include <map>

bool default_constructed = false;
bool constructed = false;
bool assigned = false;

class C {
public:
    C() { default_constructed = true; }
    C(int) { constructed = true; }
    C& operator=(const C&) { assigned = true; return *this;}
};

int main() {
    std::map<int, C> m;
    m[7] = C(1);

    std::cout << default_constructed << constructed << assigned;
}

// Output: 111
//The = in m[7] = C(1) calls the copy assignment operator to copy assign the newly created C(1) to the previously default constructed C inside the map, setting assigned to true.


//To avoid the default construction followed by a copy assignment, you can use one of the following:
//
//m.insert(pair<int, C>(7, C(1)));
//m.emplace(7, C(1));
