// C++ program to demonstrate
// Operator Overloading or
// Compile-Time Polymorphism
#include <iostream>
using namespace std;

class Fraction
{
  private:
    int num, den;  // Private members for numerator and denominator

  public:
    Fraction(int n, int d)  // Constructor to initialize the fraction
    {
        num = n;
        den = d;
    }

    // Conversion operator: return float value of fraction
    operator float() const  // Special member function for conversion to float
    {
        return float(num) / float(den);  // Compute decimal value
    }
};


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
    
    
    Fraction f(2, 5);  // Create a Fraction object representing 2/5
    float val = f;     // Implicitly convert Fraction to float
    cout << val << '\n';  // Output: 0.4
    return 0;
    
    
}

