//A conversion constructor is a single-parameter constructor that is declared without the function specifier explicitly. The compiler uses conversion constructors to convert objects from the type of the first parameter to the type of the conversion constructor's class.
#include <iostream>

class MyClass {
    int a, b;

public:
    MyClass(int i)
    {
        a = i;
        b = i;
    }
    void display()
    {
        std::cout << " a = " << a << " b = " << b << "\n";
    }
};

int main()
{
    MyClass object(10);
    object.display();

    // Single parameter conversion constructor is invoked.
    object = 20;
    object.display();
    return 0;
}
