/*
 The keyword mutable is mainly used to allow a particular data member of a const object to be modified.
 */
/*
#include <iostream>

class A {
public:
    int x;

    // Defining mutable variable y
    // now this can be modified
    mutable int y;

    A(): x(4), y(10) {}
};

int main() {
  
    // a is created as constant
    const A a;

    // Trying to change the value
    a.y = 200;
    std::cout << a.y;

    // Uncommenting below lines
    // will throw error
    // a.x = 8;
    //cout << a.x;
  
    return 0;
}
*/



#include <iostream>

class Example {
public:
    mutable int mutableVar;  // Can be modified even in const contexts
    int normalVar;

    Example(int m, int n) : mutableVar(m), normalVar(n) {}

    // Const member function: Can't modify non-mutable members
    void print() const {
        mutableVar += 1;  // OK: mutable allows modification
        // normalVar += 1;  // Error: Can't modify non-mutable in const function

        std::cout << "Mutable: " << mutableVar << ", Normal: " << normalVar << std::endl;
    }
};

int main() {
    const Example obj(5, 10);  // Const object
    obj.print();  // Calls const function, modifies mutableVar
    obj.print();  // mutableVar incremented again
    return 0;
}
