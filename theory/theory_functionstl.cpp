//Passing a Function as a Parameter in C++

#include <iostream>
using namespace std;

int add(int x, int y) { return x + y; }

int mul(int x, int y) { return x * y; }

int invoke(int x, int y, int (*f)(int, int)) {
    return f(x, y);
}

// Function that takes function as arguemnt
int invoke2(int x, int y, function<int(int, int)> f) {
    return f(x, y);
}

class C {
public:
    int f(int a, int b) {
        return a * b;
    }
};

// Composed function
function<int(int)> cf(function<int(int)> f4,
                      function<int(int)> f5) {
    
    // Returning a lambda expression that
    // in turn returns a function
    return [f4, f5](int x) {
        
        // Apply f1 first, then f2
        return f4(f5(x));
    };
}

int main() {
  
    // Pass pointers to add & mul
    // function as required
    cout << "Addition: ";
    cout << invoke(20, 10, &add) << '\n';

    cout << "Multiplication: ";
    cout << invoke(20, 10, &mul);

    
    C c;
    // Wrapping member function of C
    function<int(C&, int, int)> calc = &C::f;

    // Call the member function using function
      if (calc)
        cout << "Product: " << calc(c, 4, 5);
      else
          cout << "No Callable Assigned";

    
    auto add = [](int x) { return x + 2; };
    auto mul = [](int x) { return x * 3; };

    function<int(int)> calca = cf(add, mul);
    cout << calca(4);
    
    return 0;
}

