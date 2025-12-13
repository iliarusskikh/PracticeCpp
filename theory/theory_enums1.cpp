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
    
    
    return 0;
}

