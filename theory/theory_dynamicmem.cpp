#include <iostream>
//dynamic memory allocation
typedef struct cust{
    int p;
    cust(int q)
        : p(q)
    {
    }
    cust() = default;
}custum;

// Driver Code
int main()
{
    //old C methods
    int n = 1;
    int*ptr = (int*)malloc(n * sizeof(int));//dynamically allocate memory
    if(ptr==NULL) //if no memory
        std::cout<<"memory is not allocated"<<"\n";
    
    //whilst calloc allocates blocks with initiated 0;
    ptr = (int*)calloc(n, sizeof(int));
    
    ptr = (int*)realloc(ptr,10*sizeof(int));//give new size to mem allocated with malloc or calloc
    free(ptr);
    
    //C++ methods
    int *p2 = NULL;
    p2 = new int;// “new” does call the constructor of a class whereas “malloc()” does not.

    //or
    int *p = new int[10];
    
    delete p2;
    delete[] p;
    p2 = nullptr;
    p = nullptr;

    custum* cu = new custum(2);
    std::cout<<cu->p<<"\n";

    delete cu; //free() frees memory but doesn’t call Destructor of a class whereas “delete” frees the memory and also calls the Destructor of the class.


    //Compile-time or Static Memory Allocation
    //static is less efficient but  faster
    
    //Run-time or Dynamic Memory Allocation

    int *pooot = new int(10);//allocated 10
    MyClass* pObj = new MyClass();
    delete pooot;
    pooot = nullptr;
    
    std::unique_ptr<int> smartPtr = std::make_unique<int>(45);
    
    return EXIT_SUCCESS;
    
}


// Memory leaks: forgetting to deallocate memory
// Dangling pointers: using memory after its been freed;
// Double deletion: deleting the same memory twice;
// Wrong delete operator: using delete instead of delete[] for arrays;
