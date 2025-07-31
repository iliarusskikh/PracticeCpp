#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Function to search for the pattern, considering bit shifts across byte boundaries
bool findPattern(uint32_t NumBytes, uint8_t data[], uint32_t pattern) {
    if (NumBytes < 4) return false;  // Pattern needs at least 4 bytes

    uint64_t bitStream = 0;  // Store at least 40 bits for shifts
    uint32_t patternSize = 32;  // The pattern is 32 bits

    // Load the first 4 bytes into bitStream
    for (uint32_t i = 0; i < 4 && i < NumBytes; i++) {
        bitStream = (bitStream << 8) | data[i];
    }

    // Search through the byte stream
    for (uint32_t i = 4; i <= NumBytes; i++) {
        // Check all bit shifts within this 40-bit window
        for (int shift = 0; shift < 8; shift++) {
            uint32_t shiftedPattern = (bitStream >> shift) & 0xFFFFFFFF;

            // If it matches, return true
            if (shiftedPattern == pattern) {
                return true;
            }

            // If at the last byte, don't access data[i]
            if (i < NumBytes) {
                // Include bits from the next byte for finer-grain shifting
                uint32_t nextBit = (data[i] >> (8 - shift)) & ((1 << shift) - 1);
                shiftedPattern = ((bitStream >> shift) & 0xFFFFFF00) | nextBit;

                if (shiftedPattern == pattern) {
                    return true;
                }
            }
        }

        // Shift in the next byte
        if (i < NumBytes) {
            bitStream = ((bitStream << 8) | data[i]) & 0xFFFFFFFFFF;  // Keep last 40 bits
        }
    }

    return false;  // No match found
}

// Example usage
int main() {
    uint8_t data1[] = {0xFE, 0x21, 0x0C, 0x3F};  // Exact match
    uint8_t data2[] = {0x0F, 0xE2, 0x10, 0xC3, 0xF0};  // Bit-shifted match
    uint8_t data3[] = {0xFF, 0xFE, 0x21, 0x0C, 0x3F, 0x00};  // Match with offset

    uint32_t pattern = 0xFE210C3F;

    printf("Test 1: %s\n", findPattern(4, data1, pattern) ? "Matched" : "Not Found");
    printf("Test 2: %s\n", findPattern(5, data2, pattern) ? "Matched" : "Not Found");
    printf("Test 3: %s\n", findPattern(6, data3, pattern) ? "Matched" : "Not Found");

    return 0;
}

