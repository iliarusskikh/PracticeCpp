#include<iostream>
using namespace std;

// Global variable
int a = 5;

int main() {
  
    // Local variable with same name as that of
      // global variable
    int a = 100;
  
      // Accessing global a
    cout << ::a;
  
      return 0;
}
