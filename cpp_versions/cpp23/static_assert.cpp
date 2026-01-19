//static assertion

//c++23 change
//"allow static_assert of non-value dependent expressions in a template context"
//but retroactive
//not c++ version dependent, compiler dependent

#include <iostream>
#include <type_traits>

template<typename T>
T func() {
    //std::is_same<T, U> is a struct that checks whether two types T and U are exactly the same.
    if constexpr (std::is_same_v<T, double>) {
        return Output{42};
    }
    else if constexpr (std::is_same_v<T, float>) {
        return T{42};
    }
    else if constexpr (std::is_same_v<T, long double>) {
        return T{42.0L};
    }
    else {
        //This is a very common helper that helps us safely trigger a compile-time error when we reach a branch we don't want to allow.
        
        //The always_false_v<T> trick makes the expression dependent on the template parameter T.
        //Because it's dependent, the compiler waits until the template is instantiated before checking it.
        static_assert(always_false_v<T>,
                      "Unsupported output type — only floating-point types are allowed");
        //c++23     static_assert(false, "Only floating-point types are supported");

    }
}

int main() {
    // func<int>();         // ← would fail nicely: "int is deliberately not supported"
    
    std::cout << func<double>() << '\n';     // prints 42
    std::cout << func<float>()  << '\n';     // prints 42
    
    return 0;
}
