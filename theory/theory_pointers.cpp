#include <iostream>


int main(){
    
    void *ptr;
    int a = 50;
    ptr = (void*)&a;
    //or
    ptr = static_cast<void*>(&a);
    
    double *ptr2 = (double*)&a;
    
    
    
    return 0;
}
