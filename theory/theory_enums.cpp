#include <iostream>


typedef int (*func_ptr2)(int, int);

int product(int u, int v) { return u * v; }


// Defining enum Year
typedef enum {
    Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
}year;
  

enum Example : unsigned char //hat to be an integer
{
    A=5, B, C
};

enum Level
{
    Error = 0, Warning, Info
};


//using scoped enums
enum class Color {
    Red,
    Green,
    Blue
};

enum class Operation{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

double calculate(double a, double b, Operation op){
    switch(op){
        case Operation::ADD:
            return a+b;
        case Operation::SUBTRACT:
            return a-b;
        case Operation::MULTIPLY:
            return a*b;
        case Operation::DIVIDE:
            return a/b;

    }
}


enum class Permissions : uint8_t{
    READ= = 0x04;
    WRITE = 0x02;
    EXECUTE = 0x01
};


// Driver Code
int main()
{
    year k = Jan;
    int i;
  
    // Traversing the year enum
    for (i = k; i <= Dec; i++)
        std::cout << i << " ";
  
    func_ptr2 new_func_ptr = &product;
    int x1 = (*new_func_ptr)(2, 4);
    std::cout<<x1;
    
    
    Level m_LogLever = Info;
    
    if (m_LogLever == 2)
        std::cout << "Kek"<<std::endl;
    
    
    Color c = Color::Red;     // strongly typed, no implicit int conversion
    
    uint8_t readPerm = static_cast<uint8_t>(Permissions::READ);

    
    return EXIT_SUCCESS;
}

