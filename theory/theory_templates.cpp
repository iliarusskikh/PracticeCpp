// C++ Program to demonstrate
// Use of template
//type safety at compile time

#include <iostream>
using namespace std;


//class tempalte
template<typename T>
class Pair{
private:
    T first;
    T second;
  
public:
    Pair(T a, T b) : first(a), second(b){}
    
    T getMax(){
        return (first > second) ? first : second;
    }
};


template<typename T, typename U = int>//default
class Container{
private:
    T data;
    T id;
  
public:
    Container(T d, U i) : data(d), id(i){}
    
    T getData(){ return data;}
    U getId(){return id;}
};





// One function works for all data types. This would work
// even for user defined types if operator '>' is overloaded
template <typename T, int N>
T myMax(T x, T y)
{
    T Arr[N];
    return (x > y) ? x : y;
}


template <typename T>
T swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}
 

template<typename T, typename U>
auto add(T a, U b){
    return a + b;
}


//generic template
template<typename T>
void display(T value){
    std::cout << value << std::endl;
}

//specialised tempalte for char*
template<>
void display(char* value){
    std::cout << "String:" <<value << std::endl;
}


//C++20
//concepts allow you to constrain tepalte parameters to specific parameters
//define a concept
template<typename T>
concept Numeric = std::is_arithmetic_v;

//use the concept to constrain a tempalte
template<Numeric T>
T add(T a, T b){
    return a+b;
}

//simplified syntax
Numeric auto multiply(Numeric auto a, Numeric auto b){
    return a* b;
}





int main()
{
    // Call myMax for int
    cout << myMax<int,4>(3, 7) << endl;
    // call myMax for double
    cout << myMax<double,5>(3.0, 7.0) << endl;
    // call myMax for char
    cout << myMax<char,1>('g', 'e') << endl;

    
    
    int x = 5, y = 10;
    swap(x,y);//compiler generates swap
    
    int num = 10;
    double val = 3.14;
    auto result1 = add(num,val);
    display(99);
    display("Heheh");
    
    return EXIT_SUCCESS;
}


//template <int N>
//class A {
//   int arr[N];
//public:
//   virtual void fun() { cout << "A::fun()"; }
//};
//
//class B : public A<2> {
//public:
//   void fun() { cout << "B::fun()"; }
//};
//
//class C : public B { };
//
//int main() {
//   A<2> *a = new C;
//   a->fun();
//   return 0;
//}




/*
 #include <iostream>
 using namespace std;

 template <class T, int max>
 int arrMin(T arr[], int n)
 {
    int m = max;
    for (int i = 0; i < n; i++)
       if (arr[i] < m)
          m = arr[i];

    return m;
 }

 int main()
 {
    int arr1[]  = {10, 20, 15, 12};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);

    char arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    cout << arrMin<int, 10000>(arr1, n1) << endl;
    cout << arrMin<char, 256>(arr2, n2);
    return 0;
 }
 */


//specialisation
/*
 #include <iostream>
 using namespace std;

 template <class T>
 T max (T &a, T &b)
 {
     return (a > b)? a : b;
 }

 template <>
 int max <int> (int &a, int &b)
 {
     cout << "Called ";
     return (a > b)? a : b;
 }

 int main ()
 {
     int a = 10, b = 20;
     cout << max <int> (a, b);
 }
 
 */





/*
 
 #include <iostream>

 template<typename T, size_t S>
 class Array
 {
 public:
     int Size() const {return S;}

 private:
     T m_Data[S];
 };


 int main()
 {
     int size = 5;
     Array<int,5> data;
     return 0;
 }

 */
