#include <iostream>
using namespace std;

class A
{
    public:
    A& operator=(const A&a)
    {
        cout << "A's assignment operator called" << endl;
        return *this;
    }
};

class B
{
    A a[2];
public:
    B& operator=(const B& other)
    //The & in B& indicates that the function returns a reference to a B object.
    {
        cout << "B's assignment operator called" << endl;
        for (int i = 0; i < 2; i++)
        {
            a[i] = other.a[i];
        }
        return *this;
    }
};

int main()
{
    B b1, b2;
    b1 = b2;
    return 0;
}


//
//#include<stdlib.h>
//#include<iostream>
//
//using namespace std;
//
//class Test {
//public:
//    void* operator new(size_t size);
//    void operator delete(void*);
//    Test() { cout<<"\n Constructor called"; }
//    ~Test() { cout<<"\n Destructor called"; }
//};
//
//void* Test::operator new(size_t size)
//{
//    cout<<"\n new called";
//    void *storage = malloc(size);
//    return storage;
//}
//
//void Test::operator delete(void *p )
//{
//    cout<<"\n delete called";
//    free(p);
//}
//
//int main()
//{
//    Test *m = new Test();
//    delete m;
//    return 0;
//}
