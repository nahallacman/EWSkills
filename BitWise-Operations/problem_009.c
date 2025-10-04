#include <stdio.h>
#include <stdint.h>

// Complete the function
uint16_t highest_set_bit(uint16_t reg) {
    uint16_t mask = 0x8000;
    // Your logic here
    while(!(mask & reg) && mask){
        mask = mask>>1;
    }
    return mask;
}

int main() {
    uint16_t reg;
    scanf("%hu", &reg);

    uint16_t result = highest_set_bit(reg);
    printf("%hu", result);
    return 0;
}