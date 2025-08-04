#include <stdio.h>

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

// Structure containing an array of function pointers
struct Calculator {
    int (*operations[3])(int, int); // Array of 3 function pointers
    const char *operation_names[3]; // Names for display
};

// Function to initialize the Calculator structure
void init_calculator(struct Calculator *calc) {
    calc->operations[0] = add;
    calc->operations[1] = subtract;
    calc->operations[2] = multiply;
    calc->operation_names[0] = "Addition";
    calc->operation_names[1] = "Subtraction";
    calc->operation_names[2] = "Multiplication";
}

// Function to perform an operation using the Calculator
int perform_operation(struct Calculator *calc, int index, int a, int b) {
    if (index >= 0 && index < 3) {
        return calc->operations[index](a, b); // Call the function via pointer
    }
    return 0; // Default return for invalid index
}

int main() {
    // Declare and initialize a Calculator instance
    struct Calculator calc;
    init_calculator(&calc);

    // Test inputs
    int a = 10, b = 5;

    // Perform and display all operations
    for (int i = 0; i < 3; i++) {
        int result = perform_operation(&calc, i, a, b);
        printf("%s of %d and %d = %d\n", calc.operation_names[i], a, b, result);
    }

    return 0;
}
