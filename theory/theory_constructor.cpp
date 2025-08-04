//#include <iostream>
//using namespace std;
//
//class Point
//{
//    int x, y;
//public:
//   Point(const Point &p) { x = p.x; y = p.y; }
//   int getX() { return x; }
//   int getY() { return y; }
//};
//
//int main()
//{
//    Point p2 = p1;//copy contructor executed
//    cout << "x = " << p2.getX() << " y = " << p2.getY();
//    return 0;
//}



//    Test *t = (Test *) malloc(sizeof(Test)); MALLOC does not call the contructor, but NEW does
//if there is no copy constructor, copiler would use a copy constructor with shallow copy, where for example, str would point to the same address.

//If a class has a constructor which can be called with a single argument, then this constructor becomes conversion constructor because such a constructor allows automatic conversion to the class being constructed.

#include <iostream>
#include <string.h>
using namespace std;

class String
{
    char *str;
public:
    String(const char *s);
    String(const String &s);
    void change(int index, char c) { str[index] = c; }
    char *get() { return str; }
    ~String() { delete[] str; }
};

String::String(const char *s)
{
    int l = strlen(s);
    str = new char[l + 1];
    strcpy(str, s);
}

String::String(const String &s)
{
    int l = strlen(s.str);
    this->str = new char[l + 1]; // Allocate memory
    strcpy(this->str, s.str);    // Copy the string
}

int main()
{
    String s1("geeksQuiz");
    String s2 = s1;  // Calls copy constructor
    s1.change(0, 'G');
    cout << s1.get() << " "; // Outputs: GeeksQuiz
    cout << s2.get();        // Outputs: geeksQuiz
    //s1 = "HelloYou"; // conversion constructor is called here.
    return 0;
}
