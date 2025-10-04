#include <stdio.h>
#include <stdint.h>

uint16_t spread_bits(uint8_t val) {
    uint16_t retval = 0;
    uint8_t mask = 0x80;
    // Your logic here
    for(int i=0; i < 8; i++){
        // Shift bit over
        retval = (retval<<1);
        // Mask in bit
        retval |= (val & mask);
        // Shift mask to get next highest bit
        mask = (mask>>1);
    }
    return retval;
    return 0;
}

int main() {
    uint8_t val;
    scanf("%hhu", &val);

    uint16_t result = spread_bits(val);
    printf("%u", result);
    return 0;
}