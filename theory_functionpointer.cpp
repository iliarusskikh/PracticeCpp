#include <iostream>

// Define a callback function type
typedef void (*CallbackFunction)();
typedef int (*myfunc)(int);


// Function that takes a callback function as an argument
void performAction(CallbackFunction callback) {
    std::cout << "Performing some action...\n";
    // Call the callback function
    callback();
}

// Example callback function
void myCallback() {
    std::cout << "Callback function \n";
}

// Function declarations
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}


int fun(int i)
{
    return 0;
}

typedef void(*funpoint)(int);
typedef int(*funarray[4])(int);


int main()
{
    myfunc lambdafun;
    lambdafun=fun;
    lambdafun(1);
    // Pass the callback function to performAction
    performAction(myCallback);
    
    int (*funcArray[3])(int, int) = { add, subtract, multiply };
    std::cout << "Add: " << funcArray[0](1, 2) << std::endl;       // Calls add(10, 5)
         
    return 0;
}
