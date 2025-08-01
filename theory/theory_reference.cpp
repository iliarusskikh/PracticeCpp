#include<iostream>
using namespace std;

class Test
{
private:
    static int count;
public:
    Test& fun();
};

int Test::count = 0;

Test& Test::fun()
{
    Test::count++;
    cout<<Test::count<<" ";
    return *this; //returns by reference without creating a copy
    //cannot use this* for static func
}

int main()
{
    Test t;
    t.fun().fun().fun().fun();//possible because of reference
    return 0;
}


//The & in Test& fun() means fun() returns a reference to a Test object (not a copy or a pointer). A reference is an alias for an existing object, allowing further operations on the same object without creating a copy.
//In this case, fun() returns *this, which is a reference to the current object (t in main()). This enables method chaining, where each call to fun() returns the same object, allowing the next fun() call to be made on it.
