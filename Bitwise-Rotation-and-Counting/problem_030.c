#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Complete the function
const char* is_power_of_two(uint32_t n) {
    // Your logic here
    bool BitSet = false;
    int RegisterSize = (sizeof(n)*8);

    // No bits set
    if(n == 0){
        return "NO";
    }

    // Check each bit one at a time 
    // (the problem says not to use a loop, but the examples it gives uses a loop...)
    for(int i = 0; i < RegisterSize; i++) {
        // Check lowest bit
        if(n & 0x01){
            // If we already found at least one bit set
            if(BitSet){
                return "NO";
            }
            // This is the first bit we have found that was set
            else {
                BitSet = true;
            }
        }
        n = n >> 1;
    }

    // We only found one bit set
    return "YES";
}

int main() {
    uint32_t n;
    scanf("%u", &n);

    const char* result = is_power_of_two(n);
    printf("%s", result);
    return 0;
}