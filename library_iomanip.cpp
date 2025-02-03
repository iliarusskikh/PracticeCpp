#include <iostream>
#include <iomanip>

int main() {
  
    // Output a new line and flush the stream
    std::cout << "Hello" << std::endl;

    // Set width to 10 for the next output
    std::cout << std::setw(10) << 42 << std::endl;

    // Set precision to 3 for floating-point numbers
    std::cout << std::setprecision(3) << 3.14159 << std::endl;

    // Use fixed-point notation
    std::cout << std::fixed << 3.14159 << std::endl;

    // Use scientific notation
    std::cout << std::scientific << 3.14159 << std::endl;

    // Show the decimal point even for whole numbers
    std::cout << std::showpoint << 42.0;
    
    std::cout<<std::flush;//flushes the output stream manually
    
    bool value = true;

    // Display boolean as true/false
    std::cout << std::boolalpha << value << std::endl;
    
    
    int n = 42;

    // Align output to the left
    std::cout << std::left << std::setw(10) << n << std::endl;

    // Align output to the right
    std::cout << std::right << std::setw(10) << n << std::endl;

    // Show positive sign for numbers
    std::cout << std::showpos << n << std::endl;

    // Don't show positive sign for numbers
    std::cout << std::noshowpos << n;
    
    //endl inserts a newline and flushes the stream, while \n only inserts a newline without flushing the stream.
    

    
    return 0;
}
