#include <iostream>
#include <type_traits>

int main() {
    if(std::is_signed<char>::value){
        std::cout << std::is_same<char, signed char>::value;
    }else{
        std::cout << std::is_same<char, unsigned char>::value;
    }
}
// Output: 0
//Plain char, signed char, and unsigned char are three distinct types.

//Type char is a distinct type that has an implementation-defined choice of “signed char” or “unsigned char” as its underlying type.
