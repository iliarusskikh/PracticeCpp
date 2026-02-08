// C++ program to demonstrate
// Operator Overloading or
// Compile-Time Polymorphism
#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0)
    {
        real = r;
        imag = i;
    }

    // This is automatically called when '+' is used with between two Complex objects
    Complex operator+(Complex const& obj)
    {
        Complex res;
        res.real = real + obj.real; //real of c1 and obj of c2
        res.imag = imag + obj.imag;
        return res;
    }
    
    void print() { cout << real << " + i" << imag << endl; }
    
    
    //output stream operator overloading
    std::ostream& operator<<(std::ostream& stream, const Complex& other){
        stream << other.real << "+" << other.imag;
        return stream;
    }
    
    //input stream
    std::istream& operator>>(std::istream& is, const Complex& other){
        char ch;
        is >> ch >> other.real >> ch >> other.imag;
        return is;
    }
    
    
    
};

// Driver code
int main()
{
    Complex c1(10, 5), c2(2, 4);
    std::cout << c1 << std::endl;
    // An example call to "operator+"
    Complex c3 = c1 + c2;
    c3.print();
}

