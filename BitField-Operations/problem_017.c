#include <stdio.h>
#include <stdint.h>

uint32_t clear_bits(uint32_t reg, uint8_t pos, uint8_t len) {
    // Your code here
    uint32_t retval = reg;
    uint32_t mask = 0;
    // first make the mask
    for(int i = 0; i < len; i++){
        mask = mask << 1;
        mask |= 1;
    }
    // Then shift it into position
    mask = mask << pos;
    // And invert it since we want to turn off bits
    mask = ~mask;
    // Finally apply mask
    retval &= mask;
    return retval;
}

int main() {
    uint32_t reg;
    uint8_t pos, len;
    scanf("%u %hhu %hhu", &reg, &pos, &len);
    printf("%u", clear_bits(reg, pos, len));
    return 0;
}