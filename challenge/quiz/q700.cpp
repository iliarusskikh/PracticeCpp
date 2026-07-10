#include <iostream>
#include <cstdint>
#include <array>
#include <span>

std::uint16_t checksum(std::span<const std::uint8_t> data){
    std::uint16_t sum = 0;
    for (std::uint8_t byte : data){
        sum += byte;
    }
    
    return sum;
}

int main(){
    
    std::array<std::uint8_t, 4> frame{0x10, 0x20, 0x30, 0x40};
    auto result = checksum(frame);
    
    std::cout << "Checksum: "<<result << '\n';
    
    
    return 0;
}

//Why std::span is Necessary
//Unifies Data Containers: It allows a single function like checksum to accept raw C-style arrays, std::vector, or std::array seamlessly.
//Prevents Pointer-Size Errors: It automatically tracks both the data pointer and the size together, eliminating the dangerous practice of passing a raw pointer and a separate size argument.
//Zero Performance Cost: It is a cheap "view" (essentially just a pointer and a length) that does not allocate memory or copy elements.
