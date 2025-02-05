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
    return 0;
}

