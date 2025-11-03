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

int main()
{
    Fraction f(2, 5);  // Create a Fraction object representing 2/5
    float val = f;     // Implicitly convert Fraction to float
    cout << val << '\n';  // Output: 0.4
    return 0;
}
