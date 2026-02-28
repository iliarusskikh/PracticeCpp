#include <iostream>

struct C {
    C() = default;
    //    C() : i(0) {}  // User-provided constructor initializes

    int i; //Compiler-generated default constructor does NOT initialize int i
    //    int i = 0;  // Default member initializer

};

C standalone() {
    std::cout << "standalone() called\n";
    return C{};
}



int main() {
    const C c;// const default-constructed object
    //const C c{};  // Value-initialization (zeroes members)

    std::cout << c.i; // Reading uninitialized int!
    
    
    C a;           // Default-init:  a.i = ??? (garbage)
    C b{};         // Value-init:    b.i = 0
    C k = {};      // Value-init:    k.i = 0
    C d = C();     // Value-init:    d.i = 0
    C e();         // FUNCTION DECLARATION! (not an object)
    e();           //would call standalone
}

/*
 We're trying to default-initialize c. This is not allowed since it is const and C has a defaulted (not user-provided) constructor.
 
 
 
 */
