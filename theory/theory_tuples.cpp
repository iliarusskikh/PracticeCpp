#include <iostream>
#include <tuple>
#include <string>

std::tuple<int, double> processValues(int inputInt, double inputDouble) {
    // Example: Modify inputs and return as tuple
    int resultInt = inputInt * 2;
    double resultDouble = inputDouble + 1.0;
    return {resultInt, resultDouble};  // Return a tuple with two values
}

int main() {
    int intVal;
    double doubleVal;
    std::tie(intVal, doubleVal) = processValues(21, 2.14);  // Pass parameters and unpack the tuple

    std::cout << "Processed integer: " << intVal << std::endl;
    std::cout << "Processed double: " << doubleVal << std::endl;

    
    
    std::tuple<int, std::string, double> person {30, "joj",4.1};
    auto t2 = std::make_tuple(111,"wrew",false);
    int i = std::get<0>(t2);//111
    
    constexpr size_t size = std::tuple_size<decltype(t2)>::value; //3
    using FirstType = std::tuple_element<0,decltype(t2)>::type; //int
    
    
    auto [age, name, gpa] = person;//bindings
    
    
    
    //to modify elements
    std::get<0>(person) = 11; //update age
    
    //concatenation - merge tuples
    auto t3 = std::make_tuple(111,"wrew",false);
    auto t4 = std::make_tuple(341,"wrewwwrer",true);

    auto combined = std::tuple_cat(t3,t4); //result (111, wrew, false, 341, weerwerq, true)
    
    return EXIT_SUCCESS;
}


/*
 #include <iostream>
 #include <tuple>

 // Function that takes two integer parameters and returns a tuple with their sum and product
 std::tuple<int, int> computeSumAndProduct(int a, int b) {
     return {a + b, a * b};  // Returns a tuple containing sum and product
 }

 int main() {
     int x = 7;
     int y = 3;

     auto [sum, product] = computeSumAndProduct(x, y);  // Structured binding (C++17+) to unpack the tuple

     // Alternative (pre-C++17): use std::tie
     // int sum, product;
     // std::tie(sum, product) = computeSumAndProduct(x, y);

     std::cout << "Sum: " << sum << std::endl;
     std::cout << "Product: " << product << std::endl;

     return 0;
 }
 */



//or use struct to return the struct

