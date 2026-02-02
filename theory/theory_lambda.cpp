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

//similar to tempaltes
auto multiply = [](auto a, auto b){
    return a*b;
}


template<typename T, typename U>
auto multiply_func(T a, U b){
    return a * b;
}


//lambda captures
//init captures c++14
auto ptr = std::make_unique<int>(10);
auto lama = [value = std::move(ptr)](){
    return *value;
}

struct Counter {
    int value = 0;
    auto get_counter(){
        return [*this](){return value;};
    }
}


//template lambdas
auto lambda = []<typename T>(T value){
    return value*2;
};

auto greeet = [](std::string name = "Guest"){
    return "Hello "+ name;
};

//capturing structured bindings (c++20)
auto [x, y] = std::make_pair(1,2);
auto lambda = [=] {return x+y;};



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
    
    std::sort(values.begin(), values.end(),
              [](int a, int b) { return a < b; });
    //std::ranges::sort(values)
    
    
    
    std::for_each(begin(values), end(values),[](int n) {std::cout << n <<', ';})
    
    
    
    /*----------------------------------------*/
    //basic lambda syntax
    auto greet = [](const std::string& name){
        return "Hello, "+ name "!";
        
    };
    std::string message = greet("Bob");
    
    int x =10;
    int y = 44;
    
    auto val_lambda = [x](){
        return x*2;
    };
    
    auto ref_lambda = [&x](){
        x = 30;
        return x;
    }
    
    //using with algorithms
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};
    
    //find first even number
    auto even = std::find_if(numbers.begin(), numbers.end(), [](int n){return n % 2; });
    
    //transform all numbers mult by 2
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int n){return n * 2; });
    
    //mutable keyword allows modifying copy within lambda
    
    int cnt = 0;
    auto incr = [cnt]() mutable {
        return ++cnt;//modifies captured copy
    };
    
    std::cout <<incr(); //1
    std::cout <<incr(); //2
    std::cout <<cnt; //0!!!
    
    
    
    int result1 = multiply(5,10); //int * int
    int result2 = multiply(4.3,2.1);
    
    
    std::vector<int> vecs = {1,2,3,4,5,6,7,8,9,10};
    //sort by custom criteria
    std::sort(vecs.begin(), vecs.end(),
        [](int a, int b){
        return std::abs(a) < std::abs(b);
    });
    
    //concise transformation
    std::transform(vecs.begin(), vecs.end(), vecs.begin(), [](int n){
        return n*n;
    }); 
    
    return EXIT_SUCCESS;
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
