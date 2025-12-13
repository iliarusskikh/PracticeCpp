//dynamic arrays in C
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* items;
    size_t count;
    size_t capacity;
    
} Numbers;

int main(void)
{
    Numbers xs = {0}; //push into a stack
    
    for (int x = 0; x < 10; ++x){
        if (xs.count >= xs.capacity){
            if (xs.capacity == 0)
                xs.capacity = 256;
            else
            {
                xs.capacity *=2;
            }

            int* new_items = realloc(xs.items, xs.capacity * sizeof(*xs.items));//ptr to a single element of type INT
            if (new_items == NULL) {
                // Handle error: free existing memory, exit, etc.
                fprintf(stderr, "Memory allocation failed\n");
                free(xs.items);
                return 1;
            }
            xs.items = new_items;
        }
        xs.items[xs.count++] = x;
    }
    
    for (size_t i=0; i< xs.count; ++i)
        printf("%d\n", xs.items[i]);
    
    return 0;
}
