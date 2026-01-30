#include <iostream>

int factorial(int n){
    if (n <=1){
        return 1;
    }
    
    return n * factorial(n-1);
}

int fibonacci(int n){
    if (n<=0){
        return 0;
    }
    
    if(n ==1){
        return 1;
    }
    
    return fibonacci(n-1)+ fibonacci(n-2);
}

// This function prints the whole sequence
void print_fibonacci_sequence(int n) {
    for (int i = 0; i <= n; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
}

//more efficient looping - Space-optimized DP
void loop_fibonacci(int n) {
    
    if (n < 0) return;
    
    long long a = 0, b = 1;
    
    for (int i = 0; i <= n; i++) {
        printf("%lld ", a);
        long long next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

// 1. Classic bottom-up DP (full table)
void fib_dp_table(int n) {
    if (n < 0) return;
    long long dp[n+1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    for (int i = 0; i <= n; i++) printf("%lld ", dp[i]);
    printf("\n");
}


//use-cases for recursion:
//tree traversal
void traversalTree(Node* node){
    if (node == nullptr) return;
    process(node->data);
    traversalTree(node->left);
    traversalTree(node->right);
}

//sorting algorithms
//quicksort partition step
quickSort(arr,low, mid-1);
quickSort(arr,mid+1, high);

//backtracking
bool solveMaze(int x, int y){
    if(isGoal(x,y)) return true;
    if(solveMaze(x+1,y)) return true;
    return solveMaze(x, y+1);
}

//dynamic programming
int fiba(int n, int* memo){
    if (memo[n] != -1) return memo[n];
    memo[n] = fib(n-1, memo) + fib(n-2, memo);
    return memo[n];
}

int main() {
    factorial(4);
    
    
    return EXIT_SUCCESS;
}

