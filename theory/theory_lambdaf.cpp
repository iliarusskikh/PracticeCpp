//Using Lambdas

#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;

// Function that takes a pointer
// to a function
int invoke(int x, int y, function<int(int, int)> func) {
    return func(x, y);
}
int mylambda(int x, int y, function<int(int,int)>f)
{
    return f(x,y);
}

// Driver Code
int main()
{
    //you pass lambdas to function parameter which expects function ptr
    cout<< mylambda(4,2,[](int x,int y)->int{return x*y;});
    // Define lambdas for addition and
    // multiplication operation where
    // we want to pass another function
    // as a parameter

    // Perform Addition
    cout << "Addition: ";
    int k = invoke(20, 10, [](int x,int y) -> int{ return x + y;});

    cout << k << '\n';

    // Perform Multiplication
    cout << "Multiplication:";
    int l = invoke(20, 10,[](int x,int y) -> int{ return x * y; });

    cout << l << '\n';
    
    
    
    std:::vector<int> values = {1,4,6,3,5};
    auto it = std::find_if(values.begin(), values.end(), [](int value) {return value>4;});

    std::cout << *it << std::endl;
    
    return 0;
}

/*
 
 #include <iostream>
 #include <vector>
 #include <algorithm>

 int main() {
     // Variable from same scope (outer scope)
     int a = 3;
     
     std::cout << "Outer scope 'a' = " << a << std::endl;
     
     // Lambda CAPTURING 'a' by value [a] - copies a=3 into lambda
     auto multiplyByA = [a](int x) -> int {
         std::cout << "Inside lambda: captured a = " << a << std::endl;
         return x * a;  // Uses captured a=3
     };
     
     // Using the lambda
     int result1 = multiplyByA(10);  // 10 * 3 = 30
     std::cout << "10 * captured_a = " << result1 << std::endl;
     
     // Even with auto parameter (C++14+ style)
     auto result2 = multiplyByA(20);  // 20 * 3 = 60
     std::cout << "20 * captured_a = " << result2 << std::endl;
     
     // Demonstrate: outer 'a' can change, but captured copy stays 3
     a = 100;  // Change outer variable
     std::cout << "Outer 'a' changed to: " << a << std::endl;
     std::cout << "Lambda still uses captured a=3: " << multiplyByA(5) << std::endl;  // 15, not 500!
     
     // Real-world example: sorting vector with lambda capturing 'a'
     std::vector<int> numbers = {1, 5, 2, 8, 3};
     std::sort(numbers.begin(), numbers.end(), [a](int x, int y) {
         return (x * a) < (y * a);  // Sort by value multiplied by captured a=3
     });
     
     std::cout << "\nSorted by (value * captured_a): ";
     for (int n : numbers) {
         std::cout << n << " ";
     }
     std::cout << std::endl;
     
     return 0;
 }
 */
