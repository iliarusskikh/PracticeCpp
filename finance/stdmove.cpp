//std::move
#include <iostream>
#include <string>
#include <utility> //required for std::move

int main(){
    
    std::string origital = "Hello World";
    std::string copy = origital; //copy the string - creates a new copy of the data
    
    
    //moving the string, transfwers ownership of the data from original to moved
    //original is left in a valid but unspecified state  (often empty for strings)
    std::cout << "Original: " << origital << "\nCopy: " << copy << std::endl;
    
    std::string moved = std::move(origital);
    
    std::cout << "Moved: " << moved << "\nOriginal after move: " << origital << std::endl;
    
    
    
    return 0;
}




int main() {
    std::string origital = "Hello World";
    std::string copy = origital;
    

    
    return 0;
}
