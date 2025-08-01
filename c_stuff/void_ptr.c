#include <stdio.h>
#include <string.h>

int main() {
    int num = 10;
    float f = 3.14;
    void *ptr; // Void pointer

    // Point to an integer
    ptr = &num;
    printf("Integer value: %d\n", *(int *)ptr); // Cast to int* to dereference

    // Point to a float
    ptr = &f;
    printf("Float value: %.2f\n", *(float *)ptr); // Cast to float* to dereference

    
    //Dynamic Memory Allocation: Functions like malloc and calloc return void *, allowing allocation for any data type.
    int *arr = (int *)malloc(5 * sizeof(int)); // Cast void* to int*
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    free(arr);
    
    
    //Generic Functions: Void pointers are used in functions that operate on different data types, e.g., memcpy.
    char src[] = "Hello";
    char dst[10];
    memcpy(dst, src, strlen(src) + 1); // Uses void* internally
    printf("%s\n", dst); // Output: Hello
    
    
    return 0;
}
