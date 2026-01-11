#include<iostream>
using namespace std;

class Test
{
    static int x;
    int *ptr;
    int y;
};

int main()
{
    Test t;
    cout << sizeof(t) << " ";
    cout << sizeof(Test *);
    
    //to allocate on heap
    Test* t = new Test(); //def constructor
    
    delete t;//release memory
    
    return 0;
    
}//returns 8 4, since static not considered when sizeof, + Test* is 4 since its a pointer

//the Size of an empty structure/class is one byte

//In C++ all the uninitialized global variables are initialized to 0.




//Method over-riding can be prevented by using final as a modifier at the start of method declaration

//class Parent {
//    // Can't be overridden
//    final void show() {}
//}
//
//class Child extends Parent {
//    // This would produce error
//    void show() {}
//}



//If we declare new and [] new operators, then the objects cannot be created anywhere (within the class and outside the class) See the following example. We can not allocate an object of type Test using new.
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Test {
private:
    void* operator new(size_t size) {}
    void* operator new[](size_t size) {}
};

int main()
{
    Test *obj = new Test;//heap
    Test *arr = new Test[10];//heap
    return 0;
}
*/



//overload of a glabal function of << operator
/*
#include <iostream>
using namespace std;

class Complex
{
private:
    int real;
    int imag;
public:
    Complex(int r = 0, int i =0)
    {
        real = r;
        imag = i;
    }
    friend ostream & operator << (ostream &out, const Complex &c);
};

ostream & operator << (ostream &out, const Complex &c)
{
    out << c.real;
    out << "+i" << c.imag;
    return out;
}

int main()
{
    Complex c1(10, 15);
    cout << c1;
    return 0;
}

*/



/*
//operators
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;
public:
    Point() : x(0), y(0) { }
    Point& operator()(int dx, int dy);
    Point operator+(const Point& other) const; // Changed to return Point, const parameter, const method

    void show() const { cout << "x = " << x << ", y = " << y << endl; } // Added endl, const
};

Point& Point::operator()(int dx, int dy)
{
    x = dx;
    y = dy;
    return *this;
}

Point Point::operator+(const Point& other) const
{
    Point result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    return result; // Return new Point object
}

int main()
{
    Point pt;
    pt(3, 2);
    pt.show(); // Outputs: x = 3, y = 2

    Point pt2;
    pt2(3, 2);
    pt = pt + pt2;

    pt.show(); // Outputs: x = 6, y = 4

    return 0;
}

*/
