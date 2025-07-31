// C++ program to illustrate the use
// of cin.get()
#include <iostream>

// Driver Code
int main()
{
    char ch[30];
    std::cin.get(ch, 25);

    // Print ch
    std::cout << ch;
    
    char name[5];

    // Reads stream of 3 characters
    std::cin.getline(name, 3);

    // Print output
    std::cout << name << std::endl;
    
    
    char gfg[20];

    // Reads stream of characters
    std::cin.read(gfg, 10);

    // Print output
    std::cout << gfg << std::endl;
}


