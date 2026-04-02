/*
 It’s not “just a pointer to char”. It is a pointer to raw memory — byte by byte.

In C++, unsigned char has a special property:
It is allowed to access the raw object representation of any type.

Because this is how:
- Serialization libraries work
- Network packet parsers operate
- Image processing engines read pixels
- Cryptographic algorithms manipulate data
- Smart pointers inspect control blocks

Important distinctions:
void* → pointer to unknown type (cannot dereference)
 int x = 10;
 void* p = &x;
 *p = 5; //  illegal
 std::cout << p[0];  // illegal

 
unsigned char* → pointer to raw bytes (can dereference safely)
 1 byte - - 0 → 255
char* → may be signed depending on compiler
That difference matters in systems programming.

Modern C++ alternative?
std::byte* (C++17) — expresses intent better. But under the hood, it’s still raw bytes.
*/

#include <iostream>

int main(){
    int x = 0x12345678;//78 56 34 12
    
    //explicit cast; need to access as pointer to read sequential bytes
    unsigned char* p = reinterpret_cast<unsigned char*>(&x); //examines byte by byte
    
    //sizeof in bytes =4bytes
    for (size_t i = 0; i < sizeof(x); ++i){
        //void pointers cannot be accessed via index
        std::cout << std::hex <<static_cast<int>p[i] << " "; // 78 56 34 12 (hex values)
        //Because you're reading the actual bytes stored in memory.
        
        //unsigned char is treated by iostream as a character, not a number.
        //So the stream prints the ASCII character, not its numeric value. -> hence conversion to int required
    }
    
    
    //#include <cstddef>
    //
    //std::byte* p = reinterpret_cast<std::byte*>(&x);
    
    //    std::byte b{0xFF};
    //    To convert:
    //    std::cout <<std::hex << std::to_integer<int>(b) << "\n"

    
    return 0;
}


/*
 unsigned char* p = (unsigned char*)(&x);
 is valid but not recommended
 c-style casting would attempt to perform the following
 
 const_cast
 static_cast
 reinterpret_cast
 const_cast + reinterpret_cast
 
 
 
 
 
 reinterpret_cast is mainly for pointer reinterpretation.
 */
